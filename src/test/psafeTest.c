#include "psafeTest.h"

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

void createKeyResultLengthShouldMatchGivenArgument(void) {
  char *key = createKey("foobar", "123456", 32);
  CU_ASSERT(32 == strlen(key)};
}

void differentInputShouldCreateDifferentKey(void) {
  char *key1 = createKey("foobar", "123456", 10);
  char *key2 = createKey("foobar", "023456", 10);
  CU_ASSERT(0 != strcmp(key1, key2));
}

void sameInputShouldCreateSameKey(void) {
  char *key1 = createKey("facecbook", "123456", 10);
  char *key2 = createKey("foobar", "123456", 10);
  char *key3 = createKey("facecbook", "123456", 10);
  CU_ASSERT(0 == strcmp(key1, key3));
}

void testCreateDb(void) {
  // TODO
  CU_ASSERT(0 == 0);
}

void testEncryptDb(void) {
  // TODO
  CU_ASSERT(0 == 0);
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
   if ((NULL == CU_add_test(pSuite, "createKey() should return different keys for different input", differentInputShouldCreateDifferentKey))  ||
       (NULL == CU_add_test(pSuite, "createKey() should return the same key for the same input", sameInputShouldCreateSameKey))    ||
       (NULL == CU_add_test(pSuite, "test of encryptDb()", testEncryptDb))    ||
       (NULL == CU_add_test(pSuite, "test of createDb()", testCreateDb)))
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
