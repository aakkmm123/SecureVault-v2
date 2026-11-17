#ifndef PASSWORD_H
#define PASSWORD_H

#include "config.h"

void check_password_strength(const char *password);
void generate_random_password(char *buffer, int length);

#endif