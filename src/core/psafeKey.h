#ifndef PSAFEKEY
#define PSAFEKEY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: make createKey password typeindifferent
int createKey(char* buffer, const char *profile, const char *password, const int keySize);
int writeStringToIntArray(const char* string, int* array, const int arraySize);
int writeIntArrayToString(const int *array, char *string, const int arraySize);
int multiplicateArrayElements(int* array1, const int* array2, const int arraySize);
int addArrayElements(int* array1, const int* array2, const int arraySize);
int moduloArray(int* array, const int arraySize);
int splitAndSwapArrayAtHalf(int* array, const int arraySize);

#endif
