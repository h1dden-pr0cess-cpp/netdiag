#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

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
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char path[PATH_MAX];

        char state[32] = {0};
        char mac[64] = {0};
        char mtu[32] = {0};

        snprintf(path,
                 sizeof(path),
                 "/sys/class/net/%s/operstate",
                 entry->d_name);

        if (read_file(path, state, sizeof(state)) != 0)
        {
            strcpy(state, "unknown");
        }

        snprintf(path,
                 sizeof(path),
                 "/sys/class/net/%s/address",
                 entry->d_name);

        if (read_file(path, mac, sizeof(mac)) != 0)
        {
            strcpy(mac, "unknown");
        }

        snprintf(path,
                 sizeof(path),
                 "/sys/class/net/%s/mtu",
                 entry->d_name);

        if (read_file(path, mtu, sizeof(mtu)) != 0)
        {
            strcpy(mtu, "unknown");
        }

        printf("%-10s %-10s %-20s %-10s\n",
               entry->d_name,
               state,
               mac,
               mtu);
    }

    closedir(dir);

    return 0;
}
