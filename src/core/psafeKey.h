#ifndef PSAFEKEY
#define PSAFEKEY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayOperations.h"

void createKey(const char* buffer, const char *profile, const char *password, const int keySize);
void generateKey(const int *buffer, const int *profile, const int *password, const int keySize);
void createIntArrayFromString(const int *array, const char* string, const int keySize);

#endif
