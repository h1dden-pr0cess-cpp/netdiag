#include "interfaces.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

int take_data_from_file(const char* field, const struct dirent* entry,
                        char* path,
                        char* interface_variable)
{
    snprintf(path,
             sizeof(path),
             "/sys/class/net/%s/%s",
             entry->d_name,
             field);

    if (read_file(path,
                  interface_variable,
                  sizeof(interface_variable)) != 0)
    {
        strcpy(interface_variable, "unknown");
        return -1;
    }

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

    printf("%-10s %-10s %-20s %-10s\n",
           "IFACE",
           "STATE",
           "MAC",
           "MTU");

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
        strcmp(entry->d_name, "..") == 0) continue;
        
        char path[PATH_MAX];

        char state[32] = {0};
        char mac[64] = {0};
        char mtu[32] = {0};

        take_data_from_file("operstate",
                            entry,
                            path,
                            state);
        take_data_from_file("address",
                            entry,
                            path,
                            mac);

        take_data_from_file("mtu",
                            entry,
                            path,
                            mtu);

        printf("%-10s %-10s %-20s %-10s\n",
               entry->d_name,
               state,
               mac,
               mtu);
    }

    closedir(dir);

    return 0;
}
