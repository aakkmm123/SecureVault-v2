#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "config.h"

int save_data(const char *filename, const char *data);
char *load_data(const char *filename);
void clear_data_file(const char *filename);

#endif