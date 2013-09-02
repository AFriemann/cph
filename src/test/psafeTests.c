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
   if (   (NULL == CU_add_test(pSuite, "create_key() length should match given argument", keyLengthTestWrapper))
       || (NULL == CU_add_test(pSuite, "create_key() should return the same key for the same input", create_keySameInputTestWrapper))
       || (NULL == CU_add_test(pSuite, "create_key() should return different keys for different input", create_keyDifferentInputTestWrapper))
       || (NULL == CU_add_test(pSuite, "create_key() should work for inputs that are longer than the output key", inputLongerThanOutputTestWrapper))
       || (NULL == CU_add_test(pSuite, "conv_string_to_ints() should produce the correct int array", conv_string_to_intsTest)) )
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
   if (   (NULL == CU_add_test(pSuite, "lit_add() should return a value between 33 and 126", lit_addTest))
       || (NULL == CU_add_test(pSuite, "lit_mul() should return a value between 33 and 126", lit_mulTest))
       || (NULL == CU_add_test(pSuite, "str_to_int_array() should return the correct array", str_to_int_arrayTest))
       || (NULL == CU_add_test(pSuite, "int_array_to_str should return the correct string", int_array_to_strTest)) )
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
   if (   (NULL == CU_add_test(pSuite, "add_array() should return the correct results", add_arrayTest))
       || (NULL == CU_add_test(pSuite, "mul_array should return the correct results", mul_arrayTest))
       || (NULL == CU_add_test(pSuite, "indmul_array() should return the correct results", indmul_arrayTest)) 
       || (NULL == CU_add_test(pSuite, "reverse_indmul_array() should return the correct results", reverse_indmul_arrayTest)) ) 
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
