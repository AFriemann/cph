#ifndef LITERALOPERATIONS
#define LITERALOPERATIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int literalAddition(const int a, const int b);
int literalMultiplication(const int a, const int b);

void writeStringToIntArray(int *buffer, const char *string, const int arraySize);
void writeIntArrayToString(char *buffer, const int *intArray, const int arraySize);

#endif

