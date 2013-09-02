/*
Library containing literal operations (modulo 126) used by psafe key algorithm. 
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



#include "literalOperations.h"

int 
lit_add(const int a, const int b) {
  int result = (a + b) % 126;
  if (result < 33)
    result += 33;
  //printf("\t\t%i + %i = %i\n", a, b, result);
  return result;
}

int 
lit_sub(const int a, const int b) {
  int result = (a - b) % 126;

  /* ensure values > 0 */
  if (result < 0)
    result += 126;

  if (result < 33)
    result += 33;
  //printf("\t\t%i + %i = %i\n", a, b, result);
  return result;
}

int 
lit_mul(const int a, const int b) {
  int result = (a * b) % 126;
  if (result < 33)
    result += 33;
  //printf("\t\t%i * %i = %i\n", a, b, result);
  return result;
}

void 
str_to_int_array(int *buffer, const char *str, const int array_size) {
  int str_length = strlen (str);
 
  int index = 0;
  int iteration = 1;
  int max_index = array_size;
  int str_index = 0;

  while (index < max_index) {
    // str shorter than array
    if (str_index == str_length) {
      // if in first array round
      if (iteration == 1) {
        // reset str index 
        str_index = 0;
        str -= str_length;
      } else
        break;
    }

    if (*buffer != 0) {
      *buffer = lit_add(*buffer, *str); 
    } else {
      *buffer = *str;
    }

    // ende des arrays erreicht und noch str übrig
    if (str_length - str_index > 0 && index == iteration * (array_size - 1)) {
      // setze array zurück und erhöhe schleifen abbruch var
      buffer -= array_size;
      max_index += (str_length-1) - (str_index);
      index--; iteration++;
    }

    str++; buffer++; str_index++; index++;
  }
}

void 
int_array_to_str(char *str, const int *array, const int array_size) {
  int index = 0;

  while (index++ < array_size) {
    *str++ = *array++;
  }
}

