/*
 * PLink - a command-line (stdin/stdout) variant of PuTTY.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#define PUTTY_DO_GLOBALS               /* actually _define_ globals */
#include "putty.h"
#include "storage.h"
#include "tree234.h"

#include "apr_errno.h"

#define MAX_STDIN_BACKLOG 4096

typedef struct Info Info;
struct Info
{
    unsigned char *outptr;    // where to put the data
    int            outlen;    // number of bytes to get

    unsigned char *pending;   // where to put spare data
    int            pendlen;   // length of spare data
    int            pendsize;  // length of spare data buffer

    int            read;      // number of bytes read

    int            started;   // non-zero one the protocol has started

    void          *back;

    int           num;
};

static int initialised = 0;
static int count = 0;

// FIXME: these really, really need to return the error to the caller
void fatalbox(char *p, ...)
{
    va_list ap;
    fprintf(stderr, "FATAL ERROR: ");
    va_start(ap, p);
    vfprintf(stderr, p, ap);
    va_end(ap);
    fputc('\n', stderr);
    cleanup_exit(1);
}
void modalfatalbox(char *p, ...)
{
    va_list ap;
    fprintf(stderr, "FATAL ERROR: ");
    va_start(ap, p);
    vfprintf(stderr, p, ap);
    va_end(ap);
    fputc('\n', stderr);
    cleanup_exit(1);
}
void connection_fatal(void *frontend, char *p, ...)
{
    va_list ap;
    fprintf(stderr, "FATAL ERROR: ");
    va_start(ap, p);
    vfprintf(stderr, p, ap);
    va_end(ap);
    fputc('\n', stderr);
    cleanup_exit(1);
}
void cmdline_error(char *p, ...)
{
    va_list ap;
    fprintf(stderr, "plink: ");
    va_start(ap, p);
    vfprintf(stderr, p, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(1);
}

static Backend *back;
static Config cfg;

/*
 * Default settings that are specific to pterm.
 */
char *platform_default_s(const char *name)
{
    if (!strcmp(name, "X11Display"))
        return dupstr(getenv("DISPLAY"));
    if (!strcmp(name, "TermType"))
        return dupstr(getenv("TERM"));
    if (!strcmp(name, "UserName"))
        return get_username();
    return NULL;
}

int platform_default_i(const char *name, int def)
{
    if (!strcmp(name, "TermWidth") ||
        !strcmp(name, "TermHeight")) {
        struct winsize size;
        if (ioctl(0, TIOCGWINSZ, (void *)&size) >= 0)
            return (!strcmp(name, "TermWidth") ? size.ws_col : size.ws_row);
    }
    return def;
}

FontSpec platform_default_fontspec(const char *name)
{
    FontSpec ret;
    *ret.name = '\0';
    return ret;
}

Filename platform_default_filename(const char *name)
{
    Filename ret;
    if (!strcmp(name, "LogFileName"))
        strcpy(ret.path, "putty.log");
    else
        *ret.path = '\0';
    return ret;
}

char *x_get_default(const char *key)
{
    return NULL;                       /* this is a stub */
}
int term_ldisc(Terminal *term, int mode)
{
    return FALSE;
}
void ldisc_update(void *frontend, int echo, int edit)
{
}


/*
 * In Plink our selects are synchronous, so these functions are
 * empty stubs.
 */
int uxsel_input_add(int fd, int rwx) { return 0; }
void uxsel_input_remove(int id) { }


// Wait for some network data and process it.
//   check: non-zero not to block
//
// returns < 0 on error
int ssh_sftp_loop_iteration(int check)
{
    fd_set rset, wset, xset;
    int i, fdcount, fdsize, *fdlist;
    int fd, fdstate, rwx, ret, maxfd;
    struct timeval now = {0, 0};

    struct timeval *time;

    if (check)
        time = &now;  // return immediately
    else
        time = NULL;  // no time limit

    fdlist = NULL;
    fdcount = fdsize = 0;

    /* Count the currently active fds. */
    i = 0;
    for (fd = first_fd(&fdstate, &rwx); fd >= 0;
         fd = next_fd(&fdstate, &rwx)) i++;

    if (i < 1)
        return -1;                     /* doom */

    /* Expand the fdlist buffer if necessary. */
    if (i > fdsize) {
        fdsize = i + 16;
        fdlist = sresize(fdlist, fdsize, int);
    }

    FD_ZERO(&rset);
    FD_ZERO(&wset);
    FD_ZERO(&xset);
    maxfd = 0;

    /*
     * Add all currently open fds to the select sets, and store
     * them in fdlist as well.
     */
    fdcount = 0;
    for (fd = first_fd(&fdstate, &rwx); fd >= 0;
         fd = next_fd(&fdstate, &rwx)) {
        fdlist[fdcount++] = fd;
        if (rwx & 1)
            FD_SET_MAX(fd, maxfd, rset);
        if (rwx & 2)
            FD_SET_MAX(fd, maxfd, wset);
        if (rwx & 4)
            FD_SET_MAX(fd, maxfd, xset);
    }

    do {
        ret = select(maxfd, &rset, &wset, &xset, time);
    } while (ret < 0 && errno == EINTR);

    if (ret < 0) {
        perror("select");
        exit(1);
    }

    for (i = 0; i < fdcount; i++) {
        fd = fdlist[i];
        /*
         * We must process exceptional notifications before
         * ordinary readability ones, or we may go straight
         * past the urgent marker.
         */
        if (FD_ISSET(fd, &xset))
            select_result(fd, 4);
        if (FD_ISSET(fd, &rset))
            select_result(fd, 1);
        if (FD_ISSET(fd, &wset))
            select_result(fd, 2);
    }

    sfree(fdlist);

    return 0;
}



int from_backend(void *frontend, int is_stderr, const char *data, int datalen)
{
    unsigned char *p = (unsigned char *) data;
    unsigned len = (unsigned) datalen;

    Info *info = (Info *) frontend;

    /*
     * stderr data is just spouted to local stderr and otherwise
     * ignored.
     */
    if (is_stderr) {
        if (len > 0)
            fwrite(data, 1, len, stderr);
        return 0;
    }

    if (info->started)
    {
        if (info->outptr)
        {
            if ((info->outlen > 0) && (len > 0))
            {
                unsigned used = info->outlen;

                if (used > len)
                    used = len;

                memcpy(info->outptr, p, used);

                info->outptr += used;
                info->outlen -= used;
                info->read   += used;

                p            += used;

                len          -= used;
            }
        }

        if (len > 0) {
            if (info->pendsize < info->pendlen + len) {
                info->pendsize = info->pendlen + len + 4096;
                info->pending = sresize(info->pending, info->pendsize, unsigned char);
                if (!info->pending)
                    fatalbox("Out of memory");
            }
            memcpy(info->pending + info->pendlen, p, len);
            info->pendlen += len;
        }
    }

    return 0;
}


int ssh_poll(void *handle)
{
    Info *info = (Info *) handle;

    int ret = 0;

    //fprintf(stderr, " >>> %d ssh_poll\n", info->num);

    // process pending network data without blocking
    ssh_sftp_loop_iteration(1);

    if (info->pendlen)
        ret = 1;

    //fprintf(stderr, " <<< %d returns %d\n", info->num, ret);

    return 0;
}


void ssh_timeout_set(void *handle, int timeout)
{
    Info *info = (Info *) handle;

    //fprintf(stderr, " >>> %d timeout_set %d\n <<< %d returns\n", info->num, timeout, info->num);
    // do nothing for now
}


apr_status_t ssh_send(void *handle, const char *data, apr_size_t *len)
{
    apr_status_t ret;

    Info *info = (Info *) handle;

    //fprintf(stderr, " >>> %d ssh_send %d \"%.*s\"\n", info->num, *len, *len, data);

    back->send(info->back, (char *) data, *len);     // returns new amount of data buffered

    if (back->sendok(info->back))
        ret = APR_SUCCESS;
    else
        ret = APR_EOF; // better error code??

    //fprintf(stderr, " <<< %d returning code %d, written %d bytes\n", info->num, ret, *len);

    return ret;
}


int ssh_recv(void *handle, unsigned char *buf, int *len)
{
    Info *info = (Info *) handle;

    info->outptr  = buf;
    info->outlen  = *len;
    info->read    = 0;
    info->started = 1;

    int ret = APR_SUCCESS;

    //fprintf(stderr, " >>> %d ssh_recv %d\n", info->num, *len);

    //See if the pending-input block contains some of what we need
    if (info->pendlen > 0)
    {
        unsigned pendused = info->pendlen;

        if (pendused > info->outlen)
            pendused = info->outlen;

        memcpy(info->outptr, info->pending, pendused);

        memmove(info->pending, info->pending + pendused, info->pendlen - pendused);
        info->outptr  += pendused;
        info->outlen  -= pendused;
        info->pendlen -= pendused;
        info->read    += pendused;

        if (info->pendlen == 0)
        {
            sfree(info->pending);

            info->pending  = NULL;
            info->pendsize = 0;
        }
    }

    while (info->read == 0)
    {
        // block here
        if (ssh_sftp_loop_iteration(0) < 0)
        {
            ret = APR_EOF;
            break;
        }
    }

    info->outptr = NULL;
    info->outlen = 0;

    *len = info->read;

    //fprintf(stderr, "        %.*s\n", info->read, buf);
    //fprintf(stderr, " <<< %d returning %s having read %d bytes\n", info->num, ret == APR_SUCCESS ? "OK" : "EOF", info->read);

    return ret;
}




// connect to remote host and start a command
//      cmd: [in]  array of strings of the form "ssh"    "user@host" "svnserve" "-t" .. NULL
//                                               ignored              command to run
//   handle: [out] connection handle
//
// returns an error string / NULL if ok
const char *svn_ssh_init(char **argv, void **handle)
{
    int sending;
    int portnumber = -1;
    int *fdlist;
    int fd;
    int i, fdcount, fdsize, fdstate;
    int connopen;
    int exitcode;
    int errors = 0;
    int use_subsystem = 0;
    void *ldisc, *logctx;

    char *user;

    const char *err;
    char *realhost;

    //fprintf(stderr, " >>> %d svn_ssh_init\n    ", count + 1);

    do_defaults(NULL, &cfg);
    cfg.remote_cmd_ptr = NULL;

    // proccess "command line"
    if (*++argv)
    {
        char *p = *argv;
        char *r;

        r = strrchr(p, '@');

        if (r == NULL)
        {
            strncpy(cfg.host, p, sizeof(cfg.host) - 1);
            cfg.host[sizeof(cfg.host) - 1] = '\0';
            cfg.port = default_port;
        }
        else
        {
            *r++ = '\0';
            strncpy(cfg.username, p, sizeof(cfg.username) - 1);
            cfg.username[sizeof(cfg.username) - 1] = '\0';
            strncpy(cfg.host, r, sizeof(cfg.host) - 1);
            cfg.host[sizeof(cfg.host) - 1] = '\0';
            cfg.port = default_port;
        }
    }

    argv++;

    {
        char *command;
        char *p;
        int cmdlen, cmdsize;
        cmdlen = cmdsize = 0;
        command = NULL;

        while (*argv)
        {
            p = *argv;

            while (*p)
            {
                if (cmdlen >= cmdsize)
                {
                    cmdsize = cmdlen + 512;
                    command = sresize(command, cmdsize, char);
                }

                command[cmdlen++] = *p++;
            }
            if (cmdlen >= cmdsize)
            {
                cmdsize = cmdlen + 512;
                command = sresize(command, cmdsize, char);
            }

            command[cmdlen++]=' '; /* always add trailing space */

            argv++;
        }

        // change trailing blank to NUL
        if (cmdlen)
            command[--cmdlen] = '\0';

        cfg.remote_cmd_ptr = command;
        cfg.remote_cmd_ptr2 = NULL;
        cfg.nopty = TRUE;      /* command => no terminal */
    }

    if (cfg.remote_cmd_ptr == NULL)
        return "No command specified";
    if (cfg.host[0] == '\0')
        return "Empty host name";

    //fprintf(stderr, "* user (%s)  host (%s)  command (%s)\n", cfg.username, cfg.host, cfg.remote_cmd_ptr);

    // get on with it
    Info *info = snew(Info);
    memset(info, 0, sizeof(Info));

    *handle = info;

    info->num = ++count;

    if (!initialised)
    {
        sk_init();
        uxsel_init();

        ssh_get_line = console_get_line;

        initialised = 1;
    }

    cfg.proxy_type = PROXY_NONE;

    // build the array of ciphernames
//    for(i = 0; i < CIPHER_MAX; i++)
//      cfg.ssh_cipherlist[i] = ciphernames[i].v;

    /*
     * Force use of SSH. (If they got the protocol wrong we assume the
     * port is useless too.)
     */
    if (cfg.protocol != PROT_SSH) {
        cfg.protocol = PROT_SSH;
        cfg.port = 22;
    }

    // Set username
    if (cfg.username[0] == '\0') {
        user = get_username();
        if (!user)
            return "Empty user name";
        else {
            strncpy(cfg.username, user, sizeof(cfg.username) - 1);
            cfg.username[sizeof(cfg.username) - 1] = '\0';
            sfree(user);
        }
    }


//    if (user == NULL || user[0] == '\0')
//        user = getenv("SVN$User");

/*    if (user != NULL && user[0] != '\0') {
        strncpy(cfg.username, user, sizeof(cfg.username) - 1);
        cfg.username[sizeof(cfg.username) - 1] = '\0';
    }
    else
    {
        flags |= FLAG_INTERACTIVE; // prompt for user name
    }*/

    cfg.x11_forward = 0;
    cfg.agentfwd = 1;
    cfg.portfwd[0] = cfg.portfwd[1] = '\0';

    cfg.sshprot = 2;

    back = &ssh_backend;

    err = back->init(info, &info->back, &cfg, cfg.host, cfg.port, &realhost, 0);

    if (err)
        return err;

    logctx = log_init(NULL, &cfg);
    back->provide_logctx(info->back, logctx);
    console_provide_logctx(logctx);

    while (!back->sendok(info->back)) {
        if (ssh_sftp_loop_iteration(0) < 0)
            return "Socket error while authenticating";
    }

    sfree(realhost);

    //fprintf(stderr, " <<< %d returns OK\n", info->num);

    return NULL; // OK
}
