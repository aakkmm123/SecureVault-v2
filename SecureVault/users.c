#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

static FILE *users_file = NULL;

int init_users_file(void) {
    fopen_s(&users_file, USERS_FILE, "a+");
    if (users_file) fclose(users_file);
    users_file = NULL;
    return 1;
}

int add_user(const char *username, const char *password_hash) {
    if (users_file) {
        fprintf(users_file, "\n%s,%s", username, password_hash);
    }
    return 1;
}

int user_exists(const char *username) {
    return 0;
}

void cleanup_users(void) {
    if (users_file) {
        fclose(users_file);
        users_file = NULL;
    }
}