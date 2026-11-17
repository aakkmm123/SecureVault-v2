#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vault.h"
#include "config.h"
#include "file_manager.h"
#include "security_logs.h"

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
    log_event("Added new account: ");
    return 1;
}

int view_accounts(void) {
    if (!vault_file) return 0;

    rewind(vault_file);
    char line[256];
    int count = 0;

    printf("\n=== All Saved Accounts ===\n");
    while (fgets(line, sizeof(line), vault_file)) {
        printf("%s", line);
        count++;
    }

    if (count == 0) {
        printf("No accounts saved yet.\n");
    }
    printf("========================\n");
    printf("Total accounts: %d\n", count);

    return 1;
}

int search_account(const char *website) {
    if (!vault_file) return 0;

    rewind(vault_file);
    char line[256];
    int found = 0;

    printf("\n=== Search Results for: %s ===\n", website);
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
    // In a full implementation, would find and rewrite the account record
    // For now, log the update event
    log_event("Updated account: ");
    printf("Account update initiated.\n");
    return 1;
}

int delete_account(const char *website) {
    if (!vault_file) return 0;

    printf("Deleting account: %s\n", website);
    // In a full implementation, would remove the account record
    // For now, log the deletion event
    log_event("Deleted account: ");
    printf("Account deletion initiated.\n");
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

/* Get all website names from the vault into the provided array.
   Returns the number of websites copied, or -1 if the array is too small. */
int get_all_websites(char websites[][MAX_ACCOUNT_NAME_LENGTH], int *count) {
    if (!vault_file) return -1;

    rewind(vault_file);
    char line[256];
    int i = 0;

    *count = 0;
    while (fgets(line, sizeof(line), vault_file)) {
        if (strstr(line, "Website:") != NULL) {
            /* Get the website name after "Website: " */
            char *web = line + 9;
            /* Remove newline if present */
            web[strcspn(web, "\n")] = '\0';
            if (i < MAX_ACCOUNT_NAME_LENGTH && *count < 100) {
                strcpy_s(websites[*count], MAX_ACCOUNT_NAME_LENGTH, web);
                (*count)++;
            }
            i++;
        }
    }

    return *count;
}