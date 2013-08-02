#include "psafeKeyTest.h"

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
  return 0; 
}

int cleanCreateKeyTest(int (*f)(void), int bufferCount) {
  bufferArray = (char**)calloc(64*bufferCount,sizeof(char));
  int retval = (*f)();
  free(bufferArray);
  return retval;
}

int keyLengthTest(void) {
  createKey(*bufferArray, "foobar", "123456", 32);
  return (strlen(*bufferArray) == 32);
}

void keyLengthTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(keyLengthTest, 1));
}

int createKeyDifferentInputTest(void) {
  createKey(*bufferArray, "foobar", "123456", 10);
  createKey(*(bufferArray+1), "foobar", "023456", 10);
  return (0 != strcmp(*bufferArray, *(bufferArray+1)));
}

void createKeyDifferentInputTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(createKeyDifferentInputTest, 2));
}

int createKeySameInputTest(void) {
  createKey(*bufferArray, "facecbook", "123456", 10);
  createKey(*(bufferArray+1), "facecbook", "123456", 10);
  return (0 == strcmp(*bufferArray, *(bufferArray+1)));
}

void createKeySameInputTestWrapper(void) {
  CU_ASSERT_TRUE(cleanCreateKeyTest(createKeySameInputTest, 2));
}

int inputLongerThanOutputTest(void) {
  createKey(*bufferArray, "facebook", "123", 2);
  return (2 == strlen(*bufferArray));
}

void inputLongerThanOutputTestWrapper(void) {
  CU_ASSERT_TRUE_FATAL(cleanCreateKeyTest(inputLongerThanOutputTest, 1));
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (  (NULL == CU_add_test(pSuite, "createKey() should length should match given argument", keyLengthTestWrapper))
       || (NULL == CU_add_test(pSuite, "createKey() should return the same key for the same input", createKeySameInputTestWrapper))
       || (NULL == CU_add_test(pSuite, "createKey() should return different keys for different input", createKeyDifferentInputTestWrapper))
       //|| (NULL == CU_add_test(pSuite, "createKey() should return a valid key for input that is longer than the output key", inputLongerThanOutputTestWrapper))
       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
