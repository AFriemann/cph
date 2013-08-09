#include "arrayOperations.h"

int addArrayElements(int* array1, const int* array2, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    //printf("\n%i * %i = ", *array1, *array2);
    *array1 = literalAddition((*array1) , (*array2));  
    //printf("%i\n", *array1);
    array1++; array2++;
  }
  return 0;
}

int multiplicateArrayElements(int* array1, const int* array2, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    //printf("\n%i * %i = ", *array1, *array2);
    *array1 = literalMultiplication((*array1) , (*array2));
    //printf("%i\n", *array1);
    array1++; array2++;
  }
  return 0;
}

int arrayElementIndexMultiplication(int* array, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    //printf("\n%i * %i = ", *array, index);
    *array = literalMultiplication(*array , (index));
    //printf("%i\n", *array);
    array++;
  }
  return 0;
}

int reverseArrayElementIndexMultiplication(int* array, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    //printf("\n%i * (%i-%i) = ", *array, arraySize, index);
    *array = literalMultiplication(*array , (arraySize-index+1));
    //printf("%i\n", *array);
    array++;
  }
  return 0;
}

