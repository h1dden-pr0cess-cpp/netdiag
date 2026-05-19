#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { UNKNOWN = 0, CHECK = 1, SHOW = 2, COLLECT = 3, 
               INTERFACES = 11, ROUTES = 12, VLANS = 13, 
               LINK = 21, GATEWAY = 22} Cmd;

int show_interfaces(void) //        ./netdiag show interfaces
{

    return 0;
}

int show_routes(void) //            ./netdiag show routes
{

    return 0;
}

int show_vlans(void) //             ./netdiag show vlans
{

    return 0;
}

int check_link(const char* iface) //./netdiag check link eth0
{

    return 0;
}

int check_gateway(const char* ip) //./netdiag check gateway 192.168.1.1
{

    return 0;
}

int collect_diagnostics(void) //    ./netdiag collect
{

    return 0;
}


Cmd parse_cmd(const char *s) {
    if (s == NULL)                      return UNKNOWN;
    if (strcmp(s, "check") == 0)        return CHECK;
    if (strcmp(s, "show")  == 0)        return SHOW;
    if (strcmp(s, "collect") == 0)      return COLLECT;
    if (strcmp(s, "interfaces") == 0)   return INTERFACES;
    if (strcmp(s, "routes")  == 0)      return ROUTES;
    if (strcmp(s, "vlans") == 0)        return VLANS;
    if (strcmp(s, "link") == 0)         return LINK;
    if (strcmp(s, "gateway")  == 0)     return GATEWAY;
   

    return UNKNOWN;
}

int main(int argc, char** argv) //[0]./netdiag [1] check show collect [2] gateway[data] link[data] 
{
    if(argc < 2) return 0;

    switch (parse_cmd(argv[1]))
    {
        case SHOW:
        {
            if(argc != 3) break;

            switch (parse_cmd(argv[2]))
            {
                case INTERFACES:
                {
                    return show_interfaces();
                }
                case ROUTES:
                {
                    return show_routes();
                }
                case VLANS:
                {
                    return show_vlans();
                }
                default:
                {
                    return 0;
                }
            }

            break;
        }
        case CHECK:
        {
            if(argc != 4) break;

            switch (parse_cmd(argv[2]))
            {
                case LINK:
                {
                    return check_link(argv[3]);
                }
                case GATEWAY:
                {
                    return check_gateway(argv[3]);
                }
                default:
                {

                }
            }

            break;
        }
        case COLLECT:
        {
            if(argc != 2) break;

            collect_diagnostics();
            break;
        }
        default:
        {

        }
    }
    return 0;
}


