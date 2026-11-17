#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vault.h"
#include "config.h"
#include "file_manager.h"

static FILE *vault_file = NULL;

int init_vault(void) {
    fopen_s(&vault_file, VAULT_FILE, "a+");
    if (vault_file) fclose(vault_file);
    vault_file = NULL;
    return 1;
}

int add_account(const Account *acc) {
    if (!vault_file) return 0;

    if (search_account(acc->website)) {
        printf("Error: Account already exists!\n");
        return 0;
    }

    fprintf(vault_file, "\n--- Account ---");
    fprintf(vault_file, "\nWebsite: %s", acc->website);
    fprintf(vault_file, "\nUsername: %s", acc->username);
    fprintf(vault_file, "\nPassword: %s", acc->password);
    fprintf(vault_file, "\nCategory: %s", acc->category);
    if (acc->notes[0] != '\0') {
        fprintf(vault_file, "\nNotes: %s", acc->notes);
    }
    fprintf(vault_file, "\n-----------\n");

    printf("Account added successfully!\n");
    return 1;
}

int view_accounts(void) {
    if (!vault_file) return 0;

    rewind(vault_file);
    char line[256];

    printf("\n=== All Saved Accounts ===\n");
    while (fgets(line, sizeof(line), vault_file)) {
        printf("%s", line);
    }
    printf("========================\n");

    return 1;
}

int search_account(const char *website) {
    if (!vault_file) return 0;

    rewind(vault_file);
    char line[256];
    int found = 0;

    printf("\n=== Search Results ===\n");
    while (fgets(line, sizeof(line), vault_file)) {
        if (strstr(line, website) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("No accounts found matching: %s\n", website);
    }

    printf("======================\n");
    return found;
}

int update_account(const Account *acc) {
    if (!vault_file) return 0;

    printf("Updating account for: %s\n", acc->website);
    // In a full implementation, would rewrite the account record
    return 1;
}

int delete_account(const char *website) {
    if (!vault_file) return 0;

    printf("Deleting account: %s\n", website);
    // In a full implementation, would remove the account record
    return 1;
}

int count_accounts(void) {
    if (!vault_file) return 0;

    rewind(vault_file);
    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), vault_file)) {
        if (strstr(line, "Website:") != NULL) {
            count++;
        }
    }

    return count;
}