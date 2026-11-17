#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "password.h"

void check_password_strength(const char *password) {
    int length = (int)strlen(password);
    int has_upper = 0, has_lower = 0, has_digit = 0;

    if (length < 8) {
        printf("Password too short. Minimum 8 characters.\n");
        return;
    }

    for (int i = 0; password[i] != '\0'; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') has_upper = 1;
        if (password[i] >= 'a' && password[i] <= 'z') has_lower = 1;
        if (password[i] >= '0' && password[i] <= '9') has_digit = 1;
    }

    if (has_upper && has_lower && has_digit) {
        printf("Password strength: STRONG\n");
    } else {
        printf("Password weakness: Add uppercase, lowercase, and digit.\n");
    }
}

void generate_random_password(char *buffer, int length) {
    srand((unsigned)time(NULL));
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";

    for (int i = 0; i < length - 1; i++) {
        buffer[i] = charset[rand() % (int)sizeof(charset)];
    }
    buffer[length - 1] = '\0';
}