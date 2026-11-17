#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main(void) {
    int choice;

    printf("=== SECUREVAULT SYSTEM ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Choose an option: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (choice) {
        case 1:
            printf("Register selected.\n");
            break;
        case 2:
            printf("Login selected.\n");
            break;
        case 3:
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
    }

    return 0;
}