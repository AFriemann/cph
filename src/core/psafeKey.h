#ifndef PSAFEKEY
#define PSAFEKEY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayOperations.h"

// TODO: make createKey password typeindifferent
void createKey(char* buffer, const char *profile, const char *password, const int keySize);
//int createKey(char* buffer, const char **keyFactors, const int factorCount, const int keySize);
void createIntArrayFromString(int *array, const char* string, const int keySize);

#endif
