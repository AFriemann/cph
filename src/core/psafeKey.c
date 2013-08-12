#include "psafeKey.h"

/*
int createKey(char* buffer, const char **keyFactors, const int factorCount, const int keySize) {
  return 0;
}
*/

void createKey(char* buffer, const char *profile, const char *password, const int keySize) {

  // create array with size keysize for profile
  int *intProfile = (int*)calloc(keySize,sizeof(int));
  createIntArrayFromString(intProfile, profile, keySize);
  
  // create array with size keysize for password
  int *intPassword = (int*)calloc(keySize,sizeof(int));
  createIntArrayFromString(intPassword, password, keySize);

  // calculate key
  multiplicateArrayElements(intProfile, intPassword, keySize);
  addArrayElements(intProfile, intPassword, keySize);
 
  // write result to buffer String
  writeIntArrayToString(buffer, intProfile, keySize);
 
  //printf("foo5\n");

  free(intProfile);
  free(intPassword);
}

void createIntArrayFromString(int *array, const char* string, const int arrayLength) {
  writeStringToIntArray(array, string, arrayLength);
  shiftArrayCentre(array, arrayLength);
  arrayElementIndexMultiplication(array, arrayLength);
  reverseArrayElementIndexMultiplication(array, arrayLength);
}

