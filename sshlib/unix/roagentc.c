/*
 * Pageant client code.
 */

/*#include "windows.h"*/
#include <stdio.h>
#include <stdlib.h>

#include "kernel.h"
#include "puttymem.h"

#define AGENT_COPYDATA_ID 0x804e50ba   /* random goop */
#define AGENT_MAX_MSGLEN  8192

#ifdef TESTMODE
#define debug(x) (printf x)
#else
#define debug(x)
#endif

#define GET_32BIT(cp) (((unsigned long)(unsigned char)(cp)[0] << 24) | ((unsigned long)(unsigned char)(cp)[1] << 16) | ((unsigned long)(unsigned char)(cp)[2] << 8) | ((unsigned long)(unsigned char)(cp)[3]))

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

int agent_exists(void)
{
    _kernel_swi_regs r;
    r.r[0] = (int) "RMEnsure KeyAgent 0.01 Error KeyAgent not loaded";
    if(_kernel_swi(5 /* OS_CLI */, &r, &r) != 0) return FALSE;

    return TRUE;
}

void agent_query(void *in, int inlen, void **out, int *outlen)
{
    char *p, *ret;
    int retlen;
    _kernel_swi_regs r;

    *out = NULL;
    *outlen = 0;

    if(agent_exists() == FALSE) return;

    p = smalloc(AGENT_MAX_MSGLEN);
    if(!p) return;
    memcpy(p, in, inlen);
    r.r[1] = (int) p;
    _kernel_swi(0x568c0 /*KeyAgent_Query */, &r, &r);
    retlen = 4 + GET_32BIT(p);
    debug(("len is %d\n", retlen));
    ret = smalloc(retlen);
    if (ret)
    {
        memcpy(ret, p, retlen);
        *out = ret;
        *outlen = retlen;
    }
}

#ifdef TESTMODE

int main(void)
{
    void *msg;
    int len;
    int i;

    agent_query("\0\0\0\1\1", 5, &msg, &len);
    debug(("%d:", len));
    for (i = 0; i < len; i++)
	debug((" %02x", ((unsigned char *) msg)[i]));
    debug(("\n"));
    return 0;
}

#endif
