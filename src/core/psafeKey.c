#include "psafeKey.h"

int createKey(char* buffer, const char *profile, const char *password, const int keySize) {
 
  // create array with size keysize for profile and password
  // TODO: move intProfile to buffer
  int *intProfile = (int*)calloc(keySize,sizeof(int));
  int *intPassword = (int*)calloc(keySize,sizeof(int));
  // for given profile abc and keysize 5 produce array like 
  //    [a,b,c,a,b]
  // for given profile abcdefgh and keysize 5 produce array like
  //    [a+f,b+g,c+h,d,e]
  writeStringToIntArray(profile, intProfile, keySize);
  //moduloArray(intProfile, keySize);
  writeStringToIntArray(password, intPassword, keySize);
  //moduloArray(intPassword, keySize);
  // multiply profile array with password array as in 
  //    [pr1*pw1,pr2*pw2,pr3*pw3,...]
  multiplicateArrayElements(intProfile, intPassword, keySize);
  addArrayElements(intProfile, intPassword, keySize);
  //moduloArray(intProfile, keySize);
  // multiply profile array elements with their index as in
  //    [pr1*1,pr2*2,pr3*3,..]
  arrayElementIndexMultiplication(intProfile, keySize);
  // modulo 126 for every element: element % 126
  // if element < 33 -> element=element+33
  moduloArray(intProfile, keySize);

  // write result to buffer String
  writeIntArrayToString(intProfile, buffer, keySize);
 
  free(intProfile);
  free(intPassword);

  return 0;
}

int addArrayElements(int* array1, const int* array2, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    *array1 = (*array1) + (*array2);  
    array1++; array2++;
  }
  return 0;
}

int multiplicateArrayElements(int* array1, const int* array2, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    *array1 = (*array1) * (*array2);  
    array1++; array2++;
  }
  return 0;
}

int arrayElementIndexMultiplication(int* array, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    *array = *array * (index+1);
    array++;
  }
  return 0;
}

int moduloArray(int* array, const int arraySize) {
  int index = 0;
  //printf("resulting:\n");
  while (index++ < arraySize) {
    *array = *array % 126;
    if (*array < 33)
      *array += 33;
    //printf("\t\t%i\n",*array);
    array++;
  } 
  return 0;
}

int writeStringToIntArray(const char* string, int* array, const int arraySize) {
  int stringLength = strlen(string);
 
  int index = 0;
  int maxIndex = arraySize;
  int stringIndex = 0;
  while (index <= maxIndex) {
    if (stringIndex == stringLength) {
      stringIndex = 0;
      string -= stringLength;
    }

    if (index == arraySize) {
      index = 0; 
      maxIndex = (stringLength-1) - (stringIndex-1);
      array -= arraySize;
    }

    if (*array != 0) {
      *array = *array + (int)*string; 
    } else {
      *array = (int)*string;
    }

    //printf("\t%c\t%i\n", *string, *array);
    string++; array++; stringIndex++; index++;
  }
   
  return 0;
}

int writeIntArrayToString(const int *array, char *string, const int arraySize) {
  int index = 0;
  while (index++ < arraySize) {
    *string++ = *array++;
  }
  
  return 0;
}

