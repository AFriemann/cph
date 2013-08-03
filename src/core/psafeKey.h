#ifndef PSAFEKEY
#define PSAFEKEY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "literalOperations.h"

// TODO: make createKey password typeindifferent
int createKey(char* buffer, const char *profile, const char *password, const int keySize);
//int createKey(char* buffer, const char **keyFactors, const int factorCount, const int keySize);
int multiplicateArrayElements(int* array1, const int* array2, const int arraySize);
int arrayElementIndexMultiplication(int* array, const int arraySize);
int addArrayElements(int* array1, const int* array2, const int arraySize);
int splitAndSwapArrayAtHalf(int* array, const int arraySize);

#endif
