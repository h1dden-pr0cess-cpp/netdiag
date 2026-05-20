#include "routes.h"

#include <stdio.h>

int show_routes(void)
{
    FILE* fp = popen("ip route", "r");

    if (!fp)
    {
        perror("popen");
        return 1;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("%s", buffer);
    }

    if (pclose(fp) == -1)
    {
        perror("pclose");
        return 1;
    }

    return 0;
}
