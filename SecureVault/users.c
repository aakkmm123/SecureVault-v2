#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "config.h"

static FILE *users_file = NULL;

int init_users_file(void) {
    fopen_s(&users_file, USERS_FILE, "a+");
    if (users_file) {
        fclose(users_file);
    }
    users_file = NULL;

    FILE *check = fopen(USERS_FILE, "a");
    if (check) fclose(check);
    return 1;
}

int add_user(const char *username, const char *password_hash) {
    if (!users_file) return 0;

    if (user_exists(username)) return 0;

    fprintf(users_file, "%s,%s\n", username, password_hash);
    fflush(users_file);

    return 1;
}

int user_exists(const char *username) {
    if (!users_file) return 0;

    rewind(users_file);
    char line[128];
    char stored_user[MAX_USERNAME_LENGTH];
    char stored_hash[65];

    while (fgets(line, sizeof(line), users_file)) {
        if (sscanf_s(line, "%[^,],%s", stored_user, (unsigned int)sizeof(stored_user), stored_hash, (unsigned int)sizeof(stored_hash)) == 2) {
            if (strcmp(stored_user, username) == 0) {
                fclose(users_file);
                users_file = NULL;
                return 1;
            }
        }
    }

    fclose(users_file);
    users_file = NULL;
    return 0;
}

void cleanup_users(void) {
    if (users_file) {
        fclose(users_file);
        users_file = NULL;
    }
}