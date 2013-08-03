#include "arrayOperationsTests.h"

// array and string modification tests
void printIntArray(int *array, int size) {
  int i;
  printf("\n");
  for (i = 0 ; i<size ; i++) {
    printf("[%i]", array[i]);
  }
  printf("\n");
}

void addArrayElementsTest(void) {
  int resultArray[5] = {33,34,50,36,37};
  int addedArray[5] = {1,1,1,1,13};
  int expectedArray[5] = {34,35,51,37,50};
  addArrayElements(resultArray, addedArray, 5);
  int i;
  for (i=0; i < 5; i++)
    CU_ASSERT_EQUAL(resultArray[i], expectedArray[i]);
}

void multiplicateArrayElementsTest(void) {
  int resultArray[5] = {20,16,122,1,2};
  int addedArray[5] = {2,3,1,40,3};
  int expectedArray[5] = {40,48,122,40,39};
  multiplicateArrayElements(resultArray, addedArray, 5);
  int i;
  for (i=0; i < 5; i++)
    CU_ASSERT_EQUAL(resultArray[i], expectedArray[i]);
}

void arrayElementIndexMultiplicationTest(void) {
  int resultArray[5] = {1,12,21,33,126};
  int expectedArray[5] = {34,57,63,39,33};
  arrayElementIndexMultiplication(resultArray, 5);
  int i;
  for (i=0; i < 5; i++)
    CU_ASSERT_EQUAL(resultArray[i], expectedArray[i]);
}
