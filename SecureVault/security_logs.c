#include <stdio.h>
#include <string.h>
#include "security_logs.h"

void log_event(const char *event) {
    FILE *f = fopen(SECURITY_LOGS_FILE, "a");
    if (f) {
        fprintf(f, "%s\n", event);
        fclose(f);
    }
}

void view_security_logs(void) {
    FILE *f = fopen(SECURITY_LOGS_FILE, "r");
    if (f) {
        char line[256];
        while (fgets(line, sizeof(line), f)) {
            printf("%s", line);
        }
        fclose(f);
    }
}