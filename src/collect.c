#include "collect.h"

#include <stdio.h>
#include <stdlib.h>

int collect_diagnostics(void)
{
    printf("Collecting diagnostics...\n\n");

    if (system("mkdir -p diag") != 0)
    {
        fprintf(stderr, "[ERROR] failed to create diag directory\n");
        return 1;
    }

    /*
     * Interfaces
     */

    if (system("./netdiag show interfaces > diag/interfaces.txt") == 0)
    {
        printf("[OK] interfaces.txt\n");
    }
    else
    {
        printf("[ERROR] interfaces.txt\n");
    }

    /*
     * Routes
     */

    if (system("./netdiag show routes > diag/routes.txt") == 0)
    {
        printf("[OK] routes.txt\n");
    }
    else
    {
        printf("[ERROR] routes.txt\n");
    }

    /*
     * VLANs
     */

    if (system("./netdiag show vlans > diag/vlans.txt") == 0)
    {
        printf("[OK] vlans.txt\n");
    }
    else
    {
        printf("[ERROR] vlans.txt\n");
    }

    /*
     * ip addr
     */

    if (system("ip addr > diag/ip_addr.txt") == 0)
    {
        printf("[OK] ip_addr.txt\n");
    }
    else
    {
        printf("[ERROR] ip_addr.txt\n");
    }

     /*
     * uname
     */

    if (system("uname -a > diag/system.txt") == 0)
    {
        printf("[OK] system.txt\n");
    }
    else
    {
        printf("[ERROR] system.txt\n");
    }

    printf("\nCreating archive...\n");

    /*
     * archive
     */

    if (system("tar -czf diag.tar.gz diag") == 0)
    {
        printf("[OK] diag.tar.gz\n");
    }
    else
    {
        printf("[ERROR] failed to create archive\n");
        return 1;
    }

    printf("\nDiagnostics collection completed.\n");

    return 0;
}
