#include "literalOperations.h"

int literalAddition(const int a, const int b) {
  int result = (a + b) % 126;
  if (result < 33)
    result += 33;
  //printf("\t\t%i + %i = %i\n", a, b, result);
  return result;
}

int literalSubtraction(const int a, const int b) {
  int result = (a - b) % 126;
  if (result < 33)
    result += 33;
  //printf("\t\t%i + %i = %i\n", a, b, result);
  return result;
}

int literalMultiplication(const int a, const int b) {
  int result = (a * b) % 126;
  if (result < 33)
    result += 33;
  //printf("\t\t%i * %i = %i\n", a, b, result);
  return result;
}

void writeStringToIntArray(int* array, const char* string, const int arraySize) {
  int stringLength = strlen(string);
 
  int index = 0;
  int iteration = 1;
  int maxIndex = arraySize;
  int stringIndex = 0;

  while (index < maxIndex) {
    // string shorter than array
    if (stringIndex == stringLength) {
      // if in first array round
      if (iteration == 1) {
        // reset string index 
        stringIndex = 0;
        string -= stringLength;
      } else
        break;
    }

    //printf("%i\t%i\t->", index, *array);

    if (*array != 0) {
      *array = literalAddition(*array , *string); 
    } else {
      *array = *string;
    }

    //printf("\t%c\t%i\n", *string, *array);

    // ende des arrays erreicht und noch string übrig
    if (stringLength - stringIndex > 0 && index == iteration*(arraySize-1)) {
      // setze array zurück und erhöhe schleifen abbruch var
      //printf("stringLength - stringIndex > 0 && index == iteration*(arraySize-1)\n");
      //printf("resetting %i-%i > 0 and %i == %i*(%i-1)\n", stringLength, stringIndex, index, iteration, arraySize);
      array -= arraySize;
      maxIndex += (stringLength-1) - (stringIndex);
      index--; iteration++;
    }

    string++; array++; stringIndex++; index++;
  }
}

void writeIntArrayToString(char *string, const int *array, const int arraySize) {
  int index = 0;

  while (index++ < arraySize) {
    *string++ = *array++;
  }
}

