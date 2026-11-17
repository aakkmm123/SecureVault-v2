#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vault.h"

static FILE *vault_file = NULL;

int init_vault(void) {
    fopen_s(&vault_file, VAULT_FILE, "a+");
    if (vault_file) fclose(vault_file);
    vault_file = NULL;
    return 1;
}

int add_account(const Account *acc) {
    if (vault_file) {
        fprintf(vault_file, "\nWebsite: %s", acc->website);
        fprintf(vault_file, "\nUsername: %s", acc->username);
        fprintf(vault_file, "\nPassword: %s", acc->password);
        fprintf(vault_file, "\nCategory: %s", acc->category);
        if (acc->notes[0] != '\0') {
            fprintf(vault_file, "\nNotes: %s", acc->notes);
        }
    }
    return 1;
}

int view_accounts(void) {
    if (vault_file) {
        rewind(vault_file);
        char line[256];
        while (fgets(line, sizeof(line), vault_file)) {
            printf("%s", line);
        }
    }
    return 1;
}

int search_account(const char *website) {
    if (vault_file) {
        rewind(vault_file);
        char line[256];
        while (fgets(line, sizeof(line), vault_file)) {
            if (strstr(line, website) != NULL) {
                printf("Found account for: %s\n", website);
                return 1;
            }
        }
    }
    printf("Account not found: %s\n", website);
    return 0;
}

int update_account(const Account *acc) {
    printf("Updating account for: %s\n", acc->website);
    return 1;
}

int delete_account(const char *website) {
    printf("Deleting account: %s\n", website);
    return 1;
}

int count_accounts(void) {
    return 0;
}