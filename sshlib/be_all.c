/*
 * Linking module for PuTTY proper: list the available backends
 * including ssh.
 */

#include <stdio.h>
#include "putty.h"

struct backend_list backends[] = {
    {PROT_SSH, "ssh", &ssh_backend},
    {0, NULL}
};
