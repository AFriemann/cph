#include "psafeKey.h"

int createKey(char* buffer, const char *profile, const char *password, const int keySize) {
 
  // create array with size keysize for profile and password
  // TODO: move intProfile to buffer
  int *intProfile = (int*)malloc(keySize*sizeof(int));
  int *intPassword = (int*)malloc(keySize*sizeof(int));
  // for given profile abc and keysize 5 produce array like 
  //    [a,b,c,a,b]
  // for given profile abcdefgh and keysize 5 produce array like
  //    [a+f,b+g,c+h,d,e]
  writeStringToIntArray(profile, intProfile, keySize);
  writeStringToIntArray(password, intPassword, keySize);
  // multiply profile array with password array as in 
  //    [pr1*pw1,pr2*pw2,pr3*pw3,...]
  multiplyArrayElements(intProfile, intPassword, keySize);
  // modulo 126 for every element: element % 126
  // if element < 33 -> element=element+33
  moduloArray(intProfile, keySize);
 
  free(intProfile);
  free(intPassword);

  return 0;
}

int multiplyArrayElements(int* array1, const int* array2, const int keySize) {
  //TODO
  return 0;
}

int moduloArray(int* array, const int keySize) {
  int index = 0;
  while (*array++ != NULL) {
    *array = *array % 126;
    if (*array < 33)
      *array += 33;
  } 
  return 0;
}

int writeStringToIntArray(const char* string, int* array, int arraySize) {
  // TODO 
  while (*string != '\0') {
    *result++ = (int)*string++; // copy current character to result
  }
   
  return 0;
}

