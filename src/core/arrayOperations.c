/*
Library containing operations on arrays, used by psafe key alrogithm.  
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

#include "arrayOperations.h"

void add_array(int *array1, const int *array2, const int array_size) {
  int index = 0;
  while (index++ < array_size) {
    //printf("\n%i * %i = ", *array1, *array2);
    *array1 = lit_add((*array1), (*array2));  
    //printf("%i\n", *array1);
    array1++; array2++;
  }
}

void mul_array(int *array1, const int *array2, const int array_size) {
  int index = 0;
  while (index++ < array_size) {
    //printf("\n%i * %i = ", *array1, *array2);
    *array1 = lit_mul((*array1), (*array2));
    //printf("%i\n", *array1);
    array1++; array2++;
  }
}

void indmul_array(int *array, const int array_size) {
  int index = 0;
  while (index++ < array_size) {
    //printf("\n%i * %i = ", *array, index);
    *array = lit_mul(*array , (index));
    //printf("%i\n", *array);
    array++;
  }
}

void reverse_indmul_array(int *array, const int array_size) {
  int index = 0;
  while (index++ < array_size) {
    //printf("\n%i * (%i-%i) = ", *array, array_size, index);
    *array = lit_mul(*array , (array_size - index + 1));
    //printf("%i\n", *array);
    array++;
  }
}

void shift_array_centre(int *array, const int array_size) {
  int right_element = array[(array_size / 2) + 1];
  int left_element = array[array_size / 2];
  int mid_element = array[(array_size / 2) + 1];
  
  if (array_size % 2 == 0) { /* array_size ist gerade */
    left_element = lit_add(right_element,left_element);
    right_element = lit_sub(left_element, right_element);
  } else {
    array[array_size / 2] = lit_add(left_element, right_element);
    array[(array_size / 2) + 2] = lit_sub(right_element, left_element);
    array[(array_size / 2) + 1] = lit_add(lit_mul(right_element, left_element), mid_element);
  }
}

