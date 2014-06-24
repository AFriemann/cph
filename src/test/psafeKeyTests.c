#include "psafeKeyTests.h"

int cleanCreateKeyTest(int (*f)(char **string_buffer), int bufferCount, int keyLength) {
  char **buffer_array = malloc(keyLength * bufferCount * sizeof(char));

  int i=0;
  while (i < bufferCount) {
    buffer_array[i] = calloc(64 + 1 , sizeof(char));
    i++;
  }

  int retval = (*f)(buffer_array);
  free(buffer_array);
  return retval;
}

int keyLengthTest(char **string_buffer) {
  create_key(*string_buffer, "foobar", "123456", 32);
  return (strlen(*string_buffer) == 32);
}

void keyLengthTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(keyLengthTest, 1, 32));
}

int create_keyDifferentInputTest(char **string_buffer) {
  create_key(*string_buffer, "foobar", "123456", 10);
  create_key(*(string_buffer+1), "foobar", "023456", 10);
  return (0 != strcmp(*string_buffer, *(string_buffer+1)));
}

void create_keyDifferentInputTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(create_keyDifferentInputTest, 2, 10));
}

int create_keySameInputTest(char **string_buffer) {
  create_key(*string_buffer, "facecbook", "123456", 10);
  create_key(*(string_buffer+1), "facecbook", "123456", 10);
  return (0 == strcmp(*string_buffer, *(string_buffer+1)));
}

void create_keySameInputTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(create_keySameInputTest, 2, 10));
}

int inputLongerThanOutputTest(char **string_buffer) {
  create_key(*string_buffer, "facebook", "123", 2);
  return (2 == strlen(*string_buffer));
}

void inputLongerThanOutputTestWrapper(void) {
  CU_ASSERT_TRUE_FATAL(cleanCreateKeyTest(inputLongerThanOutputTest, 1, 2));
}

void conv_string_to_intsTest(void) {
  char *test_string = "foobar";
  int *result_array = calloc(10 , sizeof(int));
  int expected_array[10] = {100,51,51,77,45,51,84,117,108,98};

  conv_string_to_ints(result_array, test_string, 10);

  int i = 0;
  while (i < 10)
  {
    CU_ASSERT_EQUAL(result_array[i], expected_array[i]);
    i++;
  }

  free(result_array); 
}

