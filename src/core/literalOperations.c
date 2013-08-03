#include "literalOperations.h"

int literalAddition(const int a, const int b) {
  int result = (a + b) % 126;
  if (result < 33)
    result += 33;
  return result;
}

int literalMultiplication(const int a, const int b) {
  int result = (a * b) % 126;
  if (result < 33)
    result += 33;
  return result;
}

void writeStringToIntArray(int* array, const char* string, const int arraySize) {
  int stringLength = strlen(string);
 
  int index = 0;
  int maxIndex = arraySize;
  int stringIndex = 0;

  while (index <= maxIndex) {
    if (stringIndex == stringLength) {
      stringIndex = 0;
      string -= stringLength;
    }

    if (index == arraySize) {
      index = 0; 
      maxIndex = (stringLength-1) - (stringIndex-1);
      array -= arraySize;
    }

    if (*array != 0) {
      *array = literalAddition(*array , (int)*string); 
    } else {
      *array = (int)*string;
    }

    //printf("\t%c\t%i\n", *string, *array);
    string++; array++; stringIndex++; index++;
  }
}

void writeIntArrayToString(char *string, const int *array, const int arraySize) {
  int index = 0;

  while (index++ < arraySize) {
    *string++ = *array++;
  }
}

