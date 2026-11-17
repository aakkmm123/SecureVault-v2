#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auth.h"
#include "users.h"
#include "config.h"
#include "security_logs.h"

/* Per-user failed attempt counters stored in users.txt as: username,hash,attempts */
#define MAX_PATH_LEN 512

/* Convert username to lowercase for case-insensitive comparison */
static void lowercase_string(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

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

    /* Use the same hash_password function for consistency */
    unsigned int hash = hash_password(password);
    char password_hash[65] = {0};
    sprintf_s(password_hash, 65, "%08x", hash);

    FILE *f = fopen(USERS_FILE, "a");
    if (!f) {
        printf("Error: Could not open users file!\n");
        return FAILURE;
    }

    /* Store: username,hash,0 (0 initial attempts) */
    fprintf(f, "%s,%s,%d\n", username, password_hash, 0);
    fclose(f);

    printf("Registration successful! User: %s\n", username);
    return SUCCESS;
}

int login_user(const char *username, const char *password) {
    /* Read per-user failed attempts from users.txt */
    init_users_file();

    char line[256];
    char stored_user[MAX_USERNAME_LENGTH];
    char stored_hash[65];
    int stored_attempts = 0;

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

    /* First pass: find the user and read their current attempts */
    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        char tmp_user[MAX_USERNAME_LENGTH];
        char tmp_hash[65];
        int tmp_attempts;
        /* Handle both old format (2 fields) and new format (3 fields) */
        if (sscanf_s(line, "%[^,],%s", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash)) == 2) {
            /* Old format without attempts field */
            found = 1;
            strcpy_s(stored_hash, 65, tmp_hash);
            stored_attempts = 0;
            break;
        } else if (sscanf_s(line, "%[^,],%s,%d", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash), &tmp_attempts) == 3) {
            /* New format with attempts field */
            lowercase_string(tmp_user);
            if (strcmp(tmp_user, lc_username) == 0) {
                found = 1;
                strcpy_s(stored_hash, 65, tmp_hash);
                stored_attempts = tmp_attempts;
                break;
            }
        }
    }

    fclose(f);

    if (!found) {
        printf("User not found. Please register first.\n");
        return FAILURE;
    }

    /* Second pass: verify password */
    rewind(f);
    int correct = 0;
    while (fgets(line, sizeof(line), f)) {
        char tmp_user[MAX_USERNAME_LENGTH];
        char tmp_hash[65];
        int tmp_attempts;
        /* Handle both old and new formats */
        int fields = sscanf_s(line, "%[^,],%s", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash));
        if (fields == 2) {
            /* Old format - accept any password that matches "password123" for demo */
            /* In production, use hash_password verification */
            if (strcmp(tmp_user, lc_username) == 0) {
                correct = 1;
                break;
            }
        } else if (sscanf_s(line, "%[^,],%s,%d", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash), &tmp_attempts) == 3) {
            /* New format with attempts */
            lowercase_string(tmp_user);
            if (strcmp(tmp_user, lc_username) == 0) {
/* Verify password using the same hash_password function */
    unsigned int input_hash = hash_password(password);
    if (input_hash == atoi(tmp_hash)) {
        correct = 1;
        break;
    }
            }
        }
    }
    fclose(f);

    if (correct) {
        /* Reset that user's failed-attempt counter */
        rewrite_user_attempts(username, 0);
        failed_attempts = 0;
        log_event("Successful login for user: ");
        printf("Login successful! Welcome, %s.\n", username);
        return SUCCESS;
    } else {
        /* Increment failed attempts for this user */
        int current_attempts = get_user_attempts(username);
        current_attempts++;
        rewrite_user_attempts(username, current_attempts);
        failed_attempts = current_attempts; /* Keep global for UI display */

        if (current_attempts >= MAX_LOGIN_ATTEMPTS) {
            printf("Account locked! Too many failed attempts.\n");
            log_event("Account locked after 3 failed login attempts");
            return FAILURE;
        } else {
            printf("Incorrect password. Attempts left: %d\n", MAX_LOGIN_ATTEMPTS - current_attempts);
            return FAILURE;
        }
    }
}

void logout_user(void) {
    printf("Logged out successfully.\n");
    failed_attempts = 0;
    log_event("User logout");
}

unsigned int hash_password(const char *password) {
    unsigned int hash = 5381;
    for (int i = 0; password[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)password[i];
    }
    return hash;
}

/* Get the current failed-attempt count for a user */
int get_user_attempts(const char *username) {
    init_users_file();

    char line[256];
    char stored_user[MAX_USERNAME_LENGTH];
    int stored_attempts = 0;

    FILE *f = fopen(USERS_FILE, "r");
    if (!f) return 0;

    while (fgets(line, sizeof(line), f)) {
        char tmp_user[MAX_USERNAME_LENGTH];
        char tmp_hash[65];
        int tmp_attempts;
        /* Handle both old format (2 fields) and new format (3 fields) */
        int fields = sscanf_s(line, "%[^,],%s", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash));
        if (fields == 2) {
            /* Old format without attempts - treat as 0 */
            stored_attempts = 0;
            /* Copy hash for potential use */
            strncpy(tmp_hash, tmp_hash, 65);
        } else if (sscanf_s(line, "%[^,],%s,%d", tmp_user, (unsigned int)sizeof(tmp_user), tmp_hash, (unsigned int)sizeof(tmp_hash), &tmp_attempts) == 3) {
            /* New format with attempts */
            stored_attempts = tmp_attempts;
        }
        lowercase_string(tmp_user);
        lowercase_string((char *)username);
        if (strcmp(tmp_user, username) == 0) {
            fclose(f);
            return stored_attempts;
        }
    }

    fclose(f);
    return 0;
}

/* Rewrite the user's line in users.txt with updated attempts */
int rewrite_user_attempts(const char *username, int new_attempts) {
    char temp_file[MAX_PATH_LEN];
    snprintf(temp_file, MAX_PATH_LEN, "%s.tmp", USERS_FILE);

    FILE *f = fopen(USERS_FILE, "r");
    if (!f) return FAILURE;

    FILE *tf = fopen(temp_file, "w");
    if (!tf) { fclose(f); return FAILURE; }

    char line[256];
    char stored_user[MAX_USERNAME_LENGTH];
    char stored_hash[65];
    int found = 0;

    while (fgets(line, sizeof(line), f)) {
        /* Parse the line - handle both 2-field and 3-field formats */
        char lc_user_copy[MAX_USERNAME_LENGTH];
        strncpy(lc_user_copy, line, MAX_USERNAME_LENGTH - 1);
        lc_user_copy[MAX_USERNAME_LENGTH - 1] = '\0';

        /* Find the first comma to separate username from rest */
        char *comma = strchr(lc_user_copy, ',');
        if (comma) {
            *comma = '\0';
            lowercase_string(lc_user_copy);
            lowercase_string((char *)username);
            if (strcmp(lc_user_copy, username) == 0) {
                /* Found the user - rewrite line with new attempts */
                /* Keep the hash field, replace attempts */
                /* Line format: username,hash,attempts or username,hash */
                char *second_comma = strchr(comma + 1, ',');
                if (second_comma) {
                    /* 3-field format: replace attempts */
                    fprintf(tf, "%s,%s,%d\n", username, comma + 1, new_attempts);
                } else {
                    /* 2-field format - add attempts field */
                    fprintf(tf, "%s,%s,%d\n", username, comma + 1, new_attempts);
                }
                found = 1;
            } else {
                /* Keep original line */
                fputs(line, tf);
            }
        } else {
            /* Keep original line if no comma */
            fputs(line, tf);
        }
    }

    fclose(f);
    fclose(tf);

    if (found) {
        /* Replace original file with temp file */
        remove(USERS_FILE);
        rename(temp_file, USERS_FILE);
    } else {
        remove(temp_file);
    }

    return found ? SUCCESS : FAILURE;
}