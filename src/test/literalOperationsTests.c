#include "literalOperationsTests.h"

void lit_addTest(void) 
{
  int *results = malloc(5 * sizeof(int)); 
  results[0] = lit_add(2,3);
  results[1] = lit_add(120,133);
  results[2] = lit_add(1012,5);
  results[3] = lit_add(0,33);
  results[4] = lit_add(12,75);

  int i=0;
  while (i++ < 5)
    CU_ASSERT_TRUE(results[i] <= 126 && results[i] >= 33);

  free(results);
}

void lit_mulTest(void) 
{
  int *results = malloc(5 * sizeof(int)); 
  results[0] = lit_mul(2,3);
  results[1] = lit_mul(120,133);
  results[2] = lit_mul(1012,5);
  results[3] = lit_mul(0,33);
  results[4] = lit_mul(12,75);

  int i=0;
  while (i++ < 5)
    CU_ASSERT_TRUE(results[i] <= 126 && results[i] >= 33);

  free(results);
}

void str_to_int_arrayTest(void) 
{
  char *test_string = "foobar";
  int *result_array = calloc(10 , sizeof(int));
  int expected_array[10] = {73,99,111,98,97,114,102,111,111,98};

  str_to_int_array(result_array, test_string, 10);

  int i = 0;
  while (i < 10)
  {
    CU_ASSERT_EQUAL(result_array[i], expected_array[i]);
    i++;
  }

  free(result_array);
}

void int_array_to_strTest(void) 
{
  int test_array[6] = {102,111,111,98,97,114};
  char *result_string = malloc(6 * sizeof(char));
  char *expected_string = "foobar";

  int_array_to_str(result_string, test_array, 6);

  CU_ASSERT_STRING_EQUAL(result_string, expected_string);

  free(result_string);
}

