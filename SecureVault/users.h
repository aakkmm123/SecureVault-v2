#ifndef USERS_H
#define USERS_H

#include "config.h"

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password_hash[65];
} User;

int init_users_file(void);
int add_user(const char *username, const char *password_hash);
int user_exists(const char *username);
void cleanup_users(void);

#endif