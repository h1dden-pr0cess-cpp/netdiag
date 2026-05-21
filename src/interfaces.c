#include "interfaces.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

int read_iface_field(const char* field, const struct dirent* entry,
                        char* path,
                        size_t path_size,

                        char* interface_variable,
                        size_t variable_size)
{
    snprintf(path,
             path_size,
             "/sys/class/net/%s/%s",
             entry->d_name,
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


int show_interfaces(void)
{
    DIR* dir = opendir("/sys/class/net");

    if (!dir)
    {
        perror("opendir");
        return 1;
    }

    printf("%-10s %-10s %-20s %-10s %-16s\n",
           "IFACE",
           "STATE",
           "MAC",
           "MTU",
           "IP");

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
        strcmp(entry->d_name, "..") == 0) continue;
        
        char path[PATH_MAX];

        char state[32] = {0};
        char mac[64] = {0};
        char mtu[32] = {0};
        char ip[64] = {0};

        read_iface_field("operstate",
                         entry,
                         path,
                         sizeof(path),
                         state,
                         sizeof(state) );

        read_iface_field("address",
                         entry,
                         path,
                         sizeof(path),
                         mac,
                         sizeof(mac)   );

        read_iface_field("mtu",
                         entry,
                         path,
                         sizeof(path),
                         mtu,
                         sizeof(mtu)   );

        read_iface_ip(   entry->d_name, 
                         ip, 
                         sizeof(ip)    );

        printf("%-10s %-10s %-20s %-10s %-18s\n",
               entry->d_name,
               state,
               mac,
               mtu,
               ip);
    }

    closedir(dir);

    return 0;
}
