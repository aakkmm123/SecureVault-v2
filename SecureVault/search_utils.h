#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H

#include "config.h"

int recursive_account_search(const char *website);
int sort_websites(char websites[][MAX_ACCOUNT_NAME_LENGTH], int count);
int binary_search_accounts(const char websites[][MAX_ACCOUNT_NAME_LENGTH], 
                          const int *count, 
                          const char *target, 
                          int low, int high);

#endif