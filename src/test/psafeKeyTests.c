#include "psafeKeyTests.h"

// createKey tests

int cleanCreateKeyTest(int (*f)(char **stringBuffer), int bufferCount, int keyLength) {
  char **bufferArray = (char**)malloc(keyLength*bufferCount*sizeof(char));

  int i=0;
  while (i < bufferCount) {
    bufferArray[i] = (char*)calloc(64+1 , sizeof(char));
    i++;
  }

  int retval = (*f)(bufferArray);
  free(bufferArray);
  return retval;
}

int keyLengthTest(char **stringBuffer) {
  createKey(*stringBuffer, "foobar", "123456", 32);
  return (strlen(*stringBuffer) == 32);
}

void keyLengthTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(keyLengthTest, 1, 32));
}

int createKeyDifferentInputTest(char **stringBuffer) {
  createKey(*stringBuffer, "foobar", "123456", 10);
  createKey(*(stringBuffer+1), "foobar", "023456", 10);
  return (0 != strcmp(*stringBuffer, *(stringBuffer+1)));
}

void createKeyDifferentInputTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(createKeyDifferentInputTest, 2, 10));
}

int createKeySameInputTest(char **stringBuffer) {
  createKey(*stringBuffer, "facecbook", "123456", 10);
  createKey(*(stringBuffer+1), "facecbook", "123456", 10);
  return (0 == strcmp(*stringBuffer, *(stringBuffer+1)));
}

void createKeySameInputTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(createKeySameInputTest, 2, 10));
}

int inputLongerThanOutputTest(char **stringBuffer) {
  createKey(*stringBuffer, "facebook", "123", 2);
  return (2 == strlen(*stringBuffer));
}

void inputLongerThanOutputTestWrapper(void) {
  CU_ASSERT_TRUE_FATAL(cleanCreateKeyTest(inputLongerThanOutputTest, 1, 2));
}

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
