#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

// Recursive binary search on sorted accounts
// Returns index of matching account, or -1 if not found
int binary_search_accounts(const char websites[][MAX_ACCOUNT_NAME_LENGTH], 
                          const int *count, 
                          const char *target, 
                          int low, int high) {
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;
    int cmp = strcmp(websites[mid], target);

    if (cmp == 0) {
        return mid;
    } else if (cmp > 0) {
        return binary_search_accounts(websites, count, target, low, mid - 1);
    } else {
        return binary_search_accounts(websites, count, target, mid + 1, high);
    }
}

int sort_websites(char websites[][MAX_ACCOUNT_NAME_LENGTH], int count) {
    char temp[MAX_ACCOUNT_NAME_LENGTH];
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(websites[j], websites[j + 1]) > 0) {
                strcpy_s(temp, sizeof(temp), websites[j]);
                strcpy_s(websites[j], MAX_ACCOUNT_NAME_LENGTH, websites[j + 1]);
                strcpy_s(websites[j + 1], MAX_ACCOUNT_NAME_LENGTH, temp);
            }
        }
    }
    
    return count;
}

int recursive_account_search(const char *website) {
    init_vault();
    
    if (!vault_file) return 0;
    
    rewind(vault_file);
    
    char websites[100][MAX_ACCOUNT_NAME_LENGTH];
    int count = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), vault_file)) {
        // Extract website name from lines starting with "Website:"
        if (strncmp(line, "Website:", 8) == 0) {
            // Get the website name after "Website: "
            char *web = line + 9;
            // Remove newline if present
            web[strcspn(web, "\n")] = '\0';
            strcpy_s(websites[count], MAX_ACCOUNT_NAME_LENGTH, web);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No accounts in vault.\n");
        return 0;
    }
    
    // Sort the websites for binary search
    sort_websites(websites, count);
    
    // Perform recursive binary search
    int index = binary_search_accounts(websites, &count, website, 0, count - 1);
    
    if (index >= 0) {
        printf("Account found using recursive binary search!\n");
        printf("Website: %s\n", websites[index]);
        return 1;
    } else {
        printf("Account not found using recursive binary search.\n");
        return 0;
    }
}