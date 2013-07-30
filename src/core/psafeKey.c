#include "psafeKey.h"

int createKey(char* buffer, const char *profile, const char *password) {
 
  int *intProfile = (int*)malloc(64*sizeof(int));
  int *intPassword = (int*)malloc(64*sizeof(int));

  *buffer='a';
 
  free(intProfile);
  free(intPassword);

  return 0;
}

int writeStringToIntArray(const char* string, int* array) {
  //int stringLength = strlen(string);
  int *result = (int*)malloc(64*sizeof(int));

  while (*string != '\0') {
    *result++ = (int)*string++; // copy current character to result
  }
   
  return 0;
}

