#ifndef VAULT_H
#define VAULT_H

#include "config.h"

typedef struct {
    char website[MAX_ACCOUNT_NAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    char notes[MAX_NOTES_LENGTH];
} Account;

int add_account(const Account *acc);
int view_accounts(void);
int search_account(const char *website);
int update_account(const Account *acc);
int delete_account(const char *website);
int count_accounts(void);

#endif