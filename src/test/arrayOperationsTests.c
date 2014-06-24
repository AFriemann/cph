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

void add_arrayTest(void) {
  int result_array[5] = {33,34,50,36,37};
  int added_array[5] = {1,1,1,1,13};
  int expected_array[5] = {34,35,51,37,50};
  
  add_array(result_array, added_array, 5);

  int i;
  for (i=0; i < 5; i++)
    CU_ASSERT_EQUAL(result_array[i], expected_array[i]);
}

void mul_arrayTest(void) {
  int result_array[5] = {20,16,122,1,2};
  int mult_array[5] = {2,3,1,40,3};
  int expected_array[5] = {40,48,122,40,39};

  mul_array(result_array, mult_array, 5);

  int i;
  for (i=0; i < 5; i++)
    CU_ASSERT_EQUAL(result_array[i], expected_array[i]);
}

void indmul_arrayTest(void) {
  int result_array[5] = {1,12,21,33,126};
  int expected_array[5] = {34,57,63,39,33};

  indmul_array(result_array, 5);

  int i;
  for (i=0; i < 5; i++)
    CU_ASSERT_EQUAL(result_array[i], expected_array[i]);
}

void reverse_indmul_arrayTest(void) {
  int result_array[5] = {1,12,21,33,126};
  int expected_array[5] = {38,48,63,66,33};

  reverse_indmul_array(result_array, 5);

  int i;
  for (i=0; i < 5; i++)
    CU_ASSERT_EQUAL(result_array[i], expected_array[i]);
}
