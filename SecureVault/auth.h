#ifndef AUTH_H
#define AUTH_H

#include "config.h"

int register_user(const char *username, const char *password);
int login_user(const char *username, const char *password);
void logout_user(void);

#endif