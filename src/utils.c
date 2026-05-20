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
