#include "psafeTests.h"

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
   pSuite = CU_add_suite("keySafe Suite", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (   (NULL == CU_add_test(pSuite, "createKey() length should match given argument", keyLengthTestWrapper))
       || (NULL == CU_add_test(pSuite, "createKey() should return the same key for the same input", createKeySameInputTestWrapper))
       || (NULL == CU_add_test(pSuite, "createKey() should return different keys for different input", createKeyDifferentInputTestWrapper)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   pSuite = CU_add_suite("literalOperations Suite", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (   (NULL == CU_add_test(pSuite, "literalAddition() should return a value between 33 and 126", literalAdditionTest))
       || (NULL == CU_add_test(pSuite, "literalMultiplication() should return a value between 33 and 126", literalMultiplicationTest))
       || (NULL == CU_add_test(pSuite, "writeStringToIntArray() should return the correct array", writeStringToIntArrayTest))
       || (NULL == CU_add_test(pSuite, "writeIntArrayToString should return the correct string", writeIntArrayToStringTest)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   pSuite = CU_add_suite("arrayOperations Suite", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (   (NULL == CU_add_test(pSuite, "addArrayElements() should return the correct results", addArrayElementsTest))
       || (NULL == CU_add_test(pSuite, "multiplicateArrayElements should return the correct results", multiplicateArrayElementsTest))
       || (NULL == CU_add_test(pSuite, "arrayElementIndexMultiplication() should return the correct results", arrayElementIndexMultiplicationTest)) )
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
