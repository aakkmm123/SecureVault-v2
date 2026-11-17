#include <stdio.h>
#include <string.h>
#include "history.h"

static FILE *history_file = NULL;

void log_login_event(int success) {
    if (!history_file) {
        fopen_s(&history_file, LOGIN_HISTORY_FILE, "a");
    }
    if (history_file) {
        fprintf(history_file, "%s login\n", success ? "Successful" : "Failed");
    }
}

void view_login_history(void) {
    if (history_file) {
        rewind(history_file);
        char line[256];
        while (fgets(line, sizeof(line), history_file)) {
            printf("%s", line);
        }
    }
}