#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "auth.h"
#include "users.h"
#include "config.h"
#include "security_logs.h"

/* Convert username to lowercase for case-insensitive comparison */
static void lowercase_string(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int register_user(const char *username, const char *password) {
    /* MUST initialize users file FIRST so user_exists() can read it */
    init_users_file();

    if (user_exists(username)) {
        printf("Error: Username already exists!\n");
        return FAILURE;
    }

    if (strlen(password) < 8) {
        printf("Error: Password must be at least 8 characters long!\n");
        return FAILURE;
    }

    /* Use the same hash_password function for consistency */
    unsigned int hash = hash_password(password);
    char password_hash[65] = {0};
    sprintf_s(password_hash, 65, "%08x", hash);

    FILE *f = fopen(USERS_FILE, "a");
    if (!f) {
        printf("Error: Could not open users file!\n");
        return FAILURE;
    }

    /* Store: username,hash (2-field format) */
    fprintf(f, "%s,%s\n", username, password_hash);
    fclose(f);

    printf("Registration successful! User: %s\n", username);
    return SUCCESS;
}

int login_user(const char *username, const char *password) {
    /* Read user data from users.txt */
    char line[256];
    char stored_user[MAX_USERNAME_LENGTH];
    char stored_hash[65];

    /* Convert username to lowercase once for comparisons */
    char lc_username[MAX_USERNAME_LENGTH];
    strncpy(lc_username, username, MAX_USERNAME_LENGTH - 1);
    lc_username[MAX_USERNAME_LENGTH - 1] = '\0';
    lowercase_string(lc_username);

    FILE *f = fopen(USERS_FILE, "r");
    if (!f) {
        printf("Error: No user records found. Register first.\n");
        return FAILURE;
    }

    /* First pass: find the user and verify password */
    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        /* Handle 2-field format: username,hash */
        char tmp_user[MAX_USERNAME_LENGTH];
        char tmp_hash[65];
        int fields = sscanf_s(line, "%[^,],%s", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash));
        if (fields == 2) {
            lowercase_string(tmp_user);
            if (strcmp(tmp_user, lc_username) == 0) {
                found = 1;
                strcpy_s(stored_hash, 65, tmp_hash);
                break;
            }
        }
    }

    fclose(f);

    if (!found) {
        printf("User not found. Please register first.\n");
        return FAILURE;
    }

    /* Second pass: verify password using hash_password */
    rewind(f);
    int correct = 0;
    while (fgets(line, sizeof(line), f)) {
        char tmp_user[MAX_USERNAME_LENGTH];
        char tmp_hash[65];
        int fields = sscanf_s(line, "%[^,],%s", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash));
        if (fields == 2) {
            lowercase_string(tmp_user);
            if (strcmp(tmp_user, lc_username) == 0) {
                /* Verify: compare hash_password(output) with stored hex hash */
                unsigned int input_hash = hash_password(password);
                /* FIX: use strtol with base 16 to properly parse hex hash string */
                if (input_hash == strtol(tmp_hash, NULL, 16)) {
                    correct = 1;
                    break;
                }
            }
        }
    }
    fclose(f);

    if (correct) {
        /* Successful login */
        log_event("Successful login for user: ");
        printf("Login successful! Welcome, %s.\n", username);
        return SUCCESS;
    } else {
        printf("Incorrect password. Please try again.\n");
        return FAILURE;
    }
}

void logout_user(void) {
    printf("Logged out successfully.\n");
    log_event("User logout");
}

unsigned int hash_password(const char *password) {
    unsigned int hash = 5381;
    for (int i = 0; password[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)password[i];
    }
    return hash;
}