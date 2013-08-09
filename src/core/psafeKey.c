#include "psafeKey.h"

/*
int createKey(char* buffer, const char **keyFactors, const int factorCount, const int keySize) {
  return 0;
}
*/

int createKey(char* buffer, const char *profile, const char *password, const int keySize) {
 
  // create array with size keysize for profile and password
  // TODO: move intProfile to buffer
  int *intProfile = (int*)calloc(keySize,sizeof(int));
  int *intPassword = (int*)calloc(keySize,sizeof(int));

  writeStringToIntArray(intProfile, profile, keySize);
  writeStringToIntArray(intPassword, password, keySize);

  arrayElementIndexMultiplication(intProfile, keySize);
  reverseArrayElementIndexMultiplication(intProfile, keySize);

  arrayElementIndexMultiplication(intPassword, keySize);
  reverseArrayElementIndexMultiplication(intPassword, keySize);
  // for given profile abc and keysize 5 produce array like 
  //    [a,b,c,a,b]
  // for given profile abcdefgh and keysize 5 produce array like
  //    [a+f,b+g,c+h,d,e]
    // multiply profile array with password array as in 
  //    [pr1*pw1,pr2*pw2,pr3*pw3,...]
  multiplicateArrayElements(intProfile, intPassword, keySize);
  addArrayElements(intProfile, intPassword, keySize);
  // multiply profile array elements with their index as in
  //    [pr1*1,pr2*2,pr3*3,..]
  // modulo 126 for every element: element % 126
  // if element < 33 -> element=element+33

  // write result to buffer String
  writeIntArrayToString(buffer, intProfile, keySize);
 
  free(intProfile);
  free(intPassword);

  return 0;
}

