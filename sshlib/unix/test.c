/**************************************
 *
 * strings.c : contains some string utils
 *
 * $Id: strings.c,v 1.3 2002/02/23 18:04:52 chris Exp $
 *
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    char buf[256];
    int want;
    int status = 0;

    void *handle;

    char *err = svn_ssh_init(argv, &handle);

    if (err)
    {
        fprintf(stderr, "%s\n", err);
        exit(-1);
    }

    while (status == 0)
    {
        want = sizeof(buf);

        status = ssh_recv(handle, buf, &want);

        for (int i = 0; i < want; i++)
            printf("%c", buf[i]);

        fflush(stdout);
    }

    sk_cleanup();

    return 0;
}
