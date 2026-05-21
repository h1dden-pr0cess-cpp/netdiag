#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <dirent.h>

int read_file(const char* path, char* buffer, size_t size);

int read_iface_field(const char* field, const char* iface,
                        char* path,
                        size_t path_size,
                        char* interface_variable,
                        size_t variable_size);

int read_iface_ip(const char* iface, char* ip, size_t size);

#endif
