#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_manager.h"

int save_data(const char *filename, const char *data) {
    FILE *f = fopen(filename, "w");
    if (f) {
        fprintf(f, "%s", data);
        fclose(f);
        return 1;
    }
    return 0;
}

char *load_data_dynamic(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

void free_data(char *data) {
    if (data) {
        free(data);
        data = NULL;
    }
}

void clear_data_file(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f) { fclose(f); }
}