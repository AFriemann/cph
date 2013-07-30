#ifndef PSAFEKEY
#define PSAFEKEY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: make createKey password typeindifferent
int createKey(char* buffer, const char *profile, const char *password);
int writeStringToIntArray(const char* string, int* array);

#endif
