#include "routes.h"

#include <stdio.h>
#include <string.h>

int parse_route_field(const char* token,
                      const char* keyword,
                      char** saveptr,
                      char* output,
                      size_t output_size)
{
    if (strcmp(token, keyword) == 0)
    {
        char* next = strtok_r(NULL, " ", saveptr);

        if (next)
        {
            strncpy(output, next, output_size - 1);
            output[output_size - 1] = '\0';

            return 1;
        }
    }

    return 0;
}

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

        char* saveptr = NULL;

        char* token = strtok_r(buffer, " \n", &saveptr);

        if (token)
        {
            strncpy(destination,
                    token,
                    sizeof(destination) - 1);

            destination[sizeof(destination) - 1] = '\0';
        }

        while (token != NULL)
        {
            parse_route_field(token,
                              "via",
                              &saveptr,
                              gateway,
                              sizeof(gateway));

            parse_route_field(token,
                              "dev",
                              &saveptr,
                              iface,
                              sizeof(iface));

            token = strtok_r(NULL, " \n", &saveptr);
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
