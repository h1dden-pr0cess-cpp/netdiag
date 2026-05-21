#include "interfaces.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>


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
                         entry->d_name,
                         path,
                         sizeof(path),
                         state,
                         sizeof(state) );

        read_iface_field("address",
                         entry->d_name,
                         path,
                         sizeof(path),
                         mac,
                         sizeof(mac)   );

        read_iface_field("mtu",
                         entry->d_name,
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
