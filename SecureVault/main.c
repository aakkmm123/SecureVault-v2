#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "auth.h"
#include "users.h"
#include "vault.h"
#include "password.h"
#include "security_logs.h"
#include "history.h"
#include "reports.h"
#include "utils.h"

int main(void) {
    int choice;
    int logged_in = 0;
    char username[MAX_USERNAME_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};
    Account acc;

    while (1) {
        if (!logged_in) {
            printf("=== SECUREVAULT SYSTEM ===\n");
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Choose an option: ");

            choice = get_valid_int_input(1, 3);

            switch (choice) {
                case 1:
                    printf("Enter username: ");
                    scanf("%49s", username);
                    printf("Enter password: ");
                    scanf("%127s", password);
                    if (register_user(username, password) == SUCCESS) {
                        log_event("User registered: ");
                    }
                    pause_program();
                    break;
                case 2:
                    printf("Enter username: ");
                    scanf("%49s", username);
                    printf("Enter password: ");
                    scanf("%127s", password);
                    if (login_user(username, password) == SUCCESS) {
                        logged_in = 1;
                        printf("Login successful! Welcome, %s.\n", username);
                        log_login_event(1);
                    } else {
                        log_login_event(0);
                    }
                    pause_program();
                    break;
                case 3:
                    printf("Goodbye!\n");
                    logout_user();
                    return 0;
            }
        } else {
            printf("=== USER DASHBOARD ===\n");
            printf("Welcome, %s\n", username);
            printf("1. Add New Account\n", username);
            printf("2. View All Accounts\n");
            printf("3. Search Account\n");
            printf("4. Update Account\n");
            printf("5. Delete Account\n");
            printf("6. Password Strength Checker\n");
            printf("7. Generate Random Password\n");
            printf("8. Security Reports\n");
            printf("9. View Login History\n");
            printf("10. View Security Logs\n");
            printf("11. Logout\n");
            printf("Choose an option: ");

            choice = get_valid_int_input(1, 11);

            switch (choice) {
                case 1:
                    printf("Enter website name: ");
                    scanf("%99s", acc.website);
                    printf("Enter username/email: ");
                    scanf("%49s", acc.username);
                    printf("Enter password: ");
                    scanf("%127s", acc.password);
                    printf("Enter category: ");
                    scanf("%49s", acc.category);
                    printf("Enter notes (optional): ");
                    scanf("%255s", acc.notes);
                    if (add_account(&acc) == SUCCESS) {
                        printf("Account added successfully!\n");
                    }
                    pause_program();
                    break;

                case 2:
                    view_accounts();
                    pause_program();
                    break;

                case 3: {
                    char search_website[MAX_ACCOUNT_NAME_LENGTH];
                    printf("Enter website to search: ");
                    scanf("%99s", search_website);
                    if (search_account(search_website) == 1) {
                        printf("Account found!\n");
                    }
                    pause_program();
                    break;
                }

                case 4:
                    printf("Enter website to update: ");
                    scanf("%99s", acc.website);
                    printf("Enter new password: ");
                    scanf("%127s", acc.password);
                    if (update_account(&acc) == SUCCESS) {
                        printf("Account updated successfully!\n");
                    }
                    pause_program();
                    break;

                case 5: {
                    char del_website[MAX_ACCOUNT_NAME_LENGTH];
                    printf("Enter website to delete: ");
                    scanf("%99s", del_website);
                    if (delete_account(del_website) == SUCCESS) {
                        printf("Account deleted successfully!\n");
                    }
                    pause_program();
                    break;
                }

                case 6: {
                    printf("Enter password to check strength: ");
                    scanf("%127s", password);
                    check_password_strength(password);
                    pause_program();
                    break;
                }

                case 7: {
                    printf("Enter password length: ");
                    int length = get_valid_int_input(8, 64);
                    char rand_pass[65];
                    generate_random_password(rand_pass, length + 1);
                    printf("Generated random password: %s\n", rand_pass);
                    pause_program();
                    break;
                }

                case 8:
                    generate_user_report();
                    generate_category_report();
                    generate_strength_report();
                    pause_program();
                    break;

                case 9:
                    view_login_history();
                    pause_program();
                    break;

                case 10:
                    view_security_logs();
                    pause_program();
                    break;

                case 11:
                    printf("Logging out...\n");
                    logged_in = 0;
                    memset(username, 0, sizeof(username));
                    memset(password, 0, sizeof(password));
                    break;
            }
        }
    }

    return 0;
}