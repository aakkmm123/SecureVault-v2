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

/* Shared file handle for users.txt - opened once, used across functions */
static FILE *users_file = NULL;

int init_users_file(void) {
    /* Open users file in append+read mode, create if doesn't exist */
    users_file = fopen(USERS_FILE, "a+");
    if (users_file) {
        fseek(users_file, 0, SEEK_SET); /* Rewind to beginning for reading */
    }
    return (users_file != NULL) ? 1 : 0;
}

int add_user(const char *username, const char *password_hash) {
    if (!users_file) return 0;

    /* Case-insensitive duplicate check */
    if (user_exists(username)) return 0;

    /* Write new user at end of file */
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
            /* No comma found - treat entire line as username (old format) */
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