#include "literalOperationsTests.h"

void literalAdditionTest(void) {
  int *results = (int*)malloc(5*sizeof(int)); 
  results[0] = literalAddition(2,3);
  results[1] = literalAddition(120,133);
  results[2] = literalAddition(1012,5);
  results[3] = literalAddition(0,33);
  results[4] = literalAddition(12,75);

  int i=0;
  while (i++ < 5)
    CU_ASSERT_TRUE(results[i] <= 126 && results[i] >= 33);

  free(results);
}

void literalMultiplicationTest(void) {
  int *results = (int*)malloc(5*sizeof(int)); 
  results[0] = literalAddition(2,3);
  results[1] = literalAddition(120,133);
  results[2] = literalAddition(1012,5);
  results[3] = literalAddition(0,33);
  results[4] = literalAddition(12,75);

  int i=0;
  while (i++ < 5)
    CU_ASSERT_TRUE(results[i] <= 126 && results[i] >= 33);

  free(results);
}

void writeStringToIntArrayTest(void) {
  char *testString = "foobar";
  int *resultArray = (int*)calloc(10,sizeof(int));
  int expectedArray[10] = {199,225,111,98,97,114,102,111,111,98};
  writeStringToIntArray(expectedArray, testString, 10);
  free(resultArray);
}

void writeIntArrayToStringTest(void) {
  char *testString = "foobar";
  int *resultArray = (int*)calloc(10,sizeof(int));
  int expectedArray[10] = {199,225,111,98,97,114,102,111,111,98};
  writeStringToIntArray(expectedArray, testString, 10);
  free(resultArray);
}

