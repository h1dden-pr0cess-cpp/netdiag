#include "routes.h"

#include <stdio.h>
#include <string.h>

int show_routes(void)
{
    FILE* fp = popen("ip route", "r");

    if (!fp)
    {
        perror("popen");
        return 1;
    }

    printf("%-20s %-20s %-10s\n",
           "DESTINATION",
           "GATEWAY",
           "IFACE");

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        char destination[64] = "-";
        char gateway[64] = "-";
        char iface[64] = "-";

        char* saveptr;

        char* token = strtok_r(buffer, " ", &saveptr);

        if (token)
        {
            strcpy(destination, token);
        }

        while (token != NULL)
        {
            if (strcmp(token, "via") == 0)
            {
                token = strtok_r(NULL, " ", &saveptr);

                if (token)
                {
                    strcpy(gateway, token);
                }
            }

            if (strcmp(token, "dev") == 0)
            {
                token = strtok_r(NULL, " ", &saveptr);

                if (token)
                {
                    strcpy(iface, token);
                }
            }

            token = strtok_r(NULL, " ", &saveptr);
        }

        printf("%-20s %-20s %-10s\n",
               destination,
               gateway,
               iface);
    }

    if (pclose(fp) == -1)
    {
        perror("pclose");
        return 1;
    }

    return 0;
}
