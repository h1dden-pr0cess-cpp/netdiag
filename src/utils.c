#include "utils.h"

#include <stdio.h>
#include <string.h>

int read_file(const char* path, char* buffer, size_t size)
{
    FILE* file = fopen(path, "r");

    if (!file)
    {
        perror("fopen");
        return -1;
    }

    if (!fgets(buffer, size, file))
    {
        fclose(file);
        return -1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    fclose(file);

    return 0;
}


int read_iface_field(const char* field, const char* iface,
                        char* path,
                        size_t path_size,

                        char* interface_variable,
                        size_t variable_size)
{
    snprintf(path,
             path_size,
             "/sys/class/net/%s/%s",
             iface,
             field);

    if (read_file(path,
                  interface_variable,
                  variable_size) != 0)
    {
        strcpy(interface_variable, "unknown");
        return -1;
    }

    return 0;
}

int read_iface_ip(const char* iface, char* ip, size_t size)
{
    char cmd[128];
    snprintf(cmd, sizeof(cmd),
             "ip -4 addr show dev %s", iface);

    FILE* fp = popen(cmd, "r");
    if (!fp)
    {
        snprintf(ip, size, "unknown");
        return 1;
    }

    char line[256];
    ip[0] = '\0';

    while (fgets(line, sizeof(line), fp))
    {
        char* start = strstr(line, "inet ");

        if (start)
        {
            start += 5;

            char* slash = strchr(start, '/');

            if (slash)
                *slash = '\0';

            strncpy(ip, start, size - 1);
            ip[size - 1] = '\0';

            break;
        }
    }

    pclose(fp);

    if (ip[0] == '\0')
        snprintf(ip, size, "-");

    return 0;
}
