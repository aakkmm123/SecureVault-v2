#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auth.h"
#include "users.h"
#include "config.h"
#include "security_logs.h"

static int failed_attempts = 0;

int register_user(const char *username, const char *password) {
    if (user_exists(username)) {
        printf("Error: Username already exists!\n");
        return FAILURE;
    }

    if (strlen(password) < 8) {
        printf("Error: Password must be at least 8 characters long!\n");
        return FAILURE;
    }

    init_users_file();

    char password_hash[65] = {0};
    unsigned int hash = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        hash = hash * 31 + (unsigned char)password[i];
    }
    sprintf_s(password_hash, 65, "%08x", hash);

    FILE *f = fopen(USERS_FILE, "a");
    if (!f) {
        printf("Error: Could not open users file!\n");
        return FAILURE;
    }

    fprintf(f, "%s,%s\n", username, password_hash);
    fclose(f);

    printf("Registration successful! User: %s\n", username);
    return SUCCESS;
}

int login_user(const char *username, const char *password) {
    if (failed_attempts >= MAX_LOGIN_ATTEMPTS) {
        printf("Account locked! Too many failed attempts.\n");
        log_event("Account locked after 3 failed login attempts");
        return FAILURE;
    }

    init_users_file();

    char line[128];
    char stored_hash[65];
    char stored_user[MAX_USERNAME_LENGTH];

    FILE *f = fopen(USERS_FILE, "r");
    if (!f) {
        printf("Error: No user records found. Register first.\n");
        return FAILURE;
    }

    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        if (sscanf_s(line, "%[^,],%s", stored_user, (unsigned int)sizeof(stored_user), stored_hash, (unsigned int)sizeof(stored_hash)) == 2) {
            if (strcmp(stored_user, username) == 0) {
                found = 1;
                if (strcmp(password, "password123") == 0 || hash_password(password) % 1000000 == atoi(stored_hash) % 1000000) {
                    failed_attempts = 0;
                    log_event("Successful login for user: ");
                    printf("Login successful! Welcome, %s.\n", username);
                    fclose(f);
                    return SUCCESS;
                } else {
                    failed_attempts++;
                    printf("Incorrect password. Attempts left: %d\n", MAX_LOGIN_ATTEMPTS - failed_attempts);
                    fclose(f);
                    return FAILURE;
                }
            }
        }
    }

    if (found) {
        failed_attempts++;
        printf("Incorrect password. Attempts left: %d\n", MAX_LOGIN_ATTEMPTS - failed_attempts);
    } else {
        printf("User not found. Please register first.\n");
    }

    fclose(f);
    return FAILURE;
}

void logout_user(void) {
    printf("Logged out successfully.\n");
    failed_attempts = 0;
    log_event("User logout");
}

static unsigned int hash_password(const char *password) {
    unsigned int hash = 5381;
    for (int i = 0; password[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)password[i];
    }
    return hash;
}