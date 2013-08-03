#include "psafeKeyTests.h"

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

