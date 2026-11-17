#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "config.h"

void encrypt_data(const char *input, char *output, int output_size, const char *key);
void decrypt_data(const char *input, char *output, int output_size, const char *key);
void generate_key_from_password(const char *password, char *key, int key_size);
int validate_encrypted_vault(const char *master_password);

#endif