#include "arrayOperations.h"

int addArrayElements(int* array1, const int* array2, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    *array1 = literalAddition((*array1) , (*array2));  
    array1++; array2++;
  }
  return 0;
}

int multiplicateArrayElements(int* array1, const int* array2, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    *array1 = literalMultiplication((*array1) , (*array2));
    array1++; array2++;
  }
  return 0;
}

int arrayElementIndexMultiplication(int* array, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    *array = literalMultiplication(*array , (index));
    array++;
  }
  return 0;
}

