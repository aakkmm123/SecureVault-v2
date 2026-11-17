#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "users.h"
#include "config.h"

/* Convert string to lowercase for case-insensitive comparison */
static void lowercase_string(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

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

    /* Case-insensitive duplicate check */
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

    while (fgets(line, sizeof(line), users_file)) {
        /* Extract just the username (before the comma) */
        char *comma = strchr(line, ',');
        if (comma) {
            int len = comma - line;
            if (len > MAX_USERNAME_LENGTH) len = MAX_USERNAME_LENGTH;
            strncpy(stored_user, line, len);
            stored_user[len] = '\0';
        } else {
            strncpy(stored_user, line, MAX_USERNAME_LENGTH - 1);
            stored_user[MAX_USERNAME_LENGTH - 1] = '\0';
        }

        /* Case-insensitive comparison */
        lowercase_string(stored_user);
        lowercase_string((char *)username);
        if (strcmp(stored_user, username) == 0) {
            fclose(users_file);
            users_file = NULL;
            return 1;
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