#include "gateway.h"

#include <stdio.h>
#include <string.h>

int check_gateway(const char* ip)
{
    char cmd[128];

    snprintf(cmd,
             sizeof(cmd),
             "ping -c 3 %s 2>&1",
             ip);

    FILE* fp = popen(cmd, "r");

    if (!fp)
    {
        perror("popen");
        return 1;
    }

    char buffer[256];

    int reachable = -1;

    printf("Checking gateway %s ...\n\n", ip);

    while (fgets(buffer, sizeof(buffer), fp))
    {
        printf("%s", buffer);

        if (strstr(buffer, "100\% packet loss"))     reachable = 0;
        else if (strstr(buffer, " 0\% packet loss")) reachable = 1;
    }

    if (pclose(fp) == -1)
    {
        perror("pclose");
        return 1;
    }

    printf("\n");

    if (reachable == 1)      printf("Gateway status: REACHABLE\n");
    else if (reachable == 0) printf("Gateway status: UNREACHABLE\n");
    else                     printf("Gateway status: UNKNOWN\n");
    

    return 0;
}
