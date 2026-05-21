#include "vlan.h"

#include <stdio.h>
#include <string.h>

int show_vlans(void)
{
    FILE* fp = popen("ip -d link show", "r");

    if (!fp)
    {
        perror("popen");
        return 1;
    }

    printf("%-10s %-10s\n",
           "INTERFACE",
           "VLAN_ID");

    char buffer[512];

    char current_iface[64] = "-";

    while (fgets(buffer, sizeof(buffer), fp))
    {  

        if (strchr(buffer, ':'))
        {
            int index;

            sscanf(buffer,
                   "%d: %63[^:@]",
                   &index,
                   current_iface);
        }

        char* vlan_pos = strstr(buffer, "vlan id");

        if (vlan_pos)
        {
            int vlan_id;

            if (sscanf(vlan_pos,
                       "vlan id %d",
                       &vlan_id) == 1)
            {
                printf("%-10s %-10d\n",
                       current_iface,
                       vlan_id);
            }
        }
    }

    if (pclose(fp) == -1)
    {
        perror("pclose");
        return 1;
    }

    return 0;
}
