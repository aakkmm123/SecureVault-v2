#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

/* Simple XOR-based encryption for educational purposes only.
   This is NOT a secure cryptographic implementation.
   Production password managers must use AES-256-GCM or better. */

static void xor_crypt(const char *input, char *output, int len, const char *key, int key_len) {
    if (len <= 0 || key_len <= 0) {
        if (output) output[0] = '\0';
        return;
    }
    for (int i = 0; i < len; i++) {
        output[i] = input[i] ^ key[i % key_len];
    }
    output[len] = '\0';
}

/* Generate a key from password using a simple hash.
   The resulting key should not be used for production security. */
void generate_key_from_password(const char *password, char *key, int key_size) {
    if (password == NULL || key == NULL || key_size <= 0) {
        if (key) key[0] = '\0';
        return;
    }

    unsigned int hash = 5381;
    int i;

    for (i = 0; password[i] != '\0' && i < key_size - 1; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)password[i];
    }
    hash = hash & 0xFFFFFFFF;

    /* Convert hash to hex string key */
    for (i = 0; i < key_size - 1; i++) {
        sprintf_s(key + i * 2, key_size - i * 2, "%02x", (hash >> (i * 8)) & 0xFF);
    }
    key[key_size - 1] = '\0';
}

void encrypt_data(const char *input, char *output, int output_size, const char *key) {
    if (input == NULL || output == NULL || key == NULL) {
        if (output) output[0] = '\0';
        return;
    }

    int key_len = (int)strlen(key);
    int input_len = (int)strlen(input);

    if (input_len >= output_size) {
        input_len = output_size - 1;
    }

    if (input_len <= 0) {
        output[0] = '\0';
        return;
    }

    xor_crypt(input, output, input_len, key, key_len);
}

void decrypt_data(const char *input, char *output, int output_size, const char *key) {
    /* XOR is symmetric: decryption is the same as encryption */
    encrypt_data(input, output, output_size, key);
}

int validate_encrypted_vault(const char *master_password) {
    if (master_password != NULL && master_password[0] != '\0') {
        return 1;
    }
    return 0;
}