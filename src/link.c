#include "utils.h"

#include <stdio.h>
#include <dirent.h>
#include <limits.h>


int check_link(const char* iface) //eth0
{
    char path[PATH_MAX];
    char state[32];
    char carrier[32];

    printf("%-12s %-12s %-12s\n",
           "Interface",
           "State",
           "Carrier");

       
    read_iface_field("operstate",
                     iface,
                     path,
                     sizeof(path),
                     state,
                     sizeof(state) );

    read_iface_field("carrier",
                     iface,
                     path,
                     sizeof(path),
                     carrier,
                     sizeof(carrier));


    printf("%-12s %-12s %-12s\n",
           iface,
           state,
           carrier);

    return 0;
}
