#include <stdio.h>
#include <ctype.h>
#include "utils.h"

void pause_program(void) {
    printf("Press Enter to continue...");
    getchar();
}

int get_valid_int_input(int min, int max) {
    int input;
    while (scanf("%d", &input) != 1 || input < min || input > max) {
        printf("Invalid input. Enter a number between %d and %d: ", min, max);
        clear_input_buffer();
    }
    clear_input_buffer();
    return input;
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}