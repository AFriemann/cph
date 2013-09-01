/*
psafe key algorithm source, generates keys.
Copyright (C) 2013 Aljosha Friemann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see [http://www.gnu.org/licenses/].
*/


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

  // create buffer array with size keysize for result
  int *resultBuffer = (int*)calloc(keySize,sizeof(int));
  generateKey(resultBuffer, intProfile, intPassword, keySize);
 
  // write result to buffer String
  writeIntArrayToString(buffer, resultBuffer, keySize);
 
  //printf("foo5\n");

  free(resultBuffer);
  free(intProfile);
  free(intPassword);
}


void generateKey(int *buffer, const int *profile, const int *password, const int keySize) {
  // copy profile to buffer
  memcpy(buffer,profile,keySize*sizeof(int));
  // calculate key
  multiplicateArrayElements(buffer, password, keySize);
  addArrayElements(buffer, password, keySize);
}

void createIntArrayFromString(int *array, const char* string, const int arrayLength) {
  writeStringToIntArray(array, string, arrayLength);
  shiftArrayCentre(array, arrayLength);
  arrayElementIndexMultiplication(array, arrayLength);
  reverseArrayElementIndexMultiplication(array, arrayLength);
}

