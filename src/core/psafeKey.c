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

void 
create_key(char *buffer, const char *profile, const char *password, const int key_size) {

  // create array with size keysize for profile
  int *profile_int = calloc(key_size, sizeof(int));
  conv_string_to_ints(profile_int, profile, key_size);
  
  // create array with size keysize for password
  int *password_int = calloc(key_size, sizeof(int));
  conv_string_to_ints(password_int, password, key_size);

  // create buffer array with size keysize for result
  int *result_buffer = calloc(key_size, sizeof(int));
  generate_key(result_buffer, profile_int, password_int, key_size);
 
  // write result to buffer String
  int_array_to_str(buffer, result_buffer, key_size);
 
  free(result_buffer);
  free(profile_int);
  free(password_int);
}


void 
generate_key(int *buffer, const int *profile, const int *password, const int key_size) {
  // copy profile to buffer
  memcpy(buffer, profile, key_size * sizeof (int));
  // calculate key
  mul_array(buffer, password, key_size);
  add_array(buffer, password, key_size);
}

void 
conv_string_to_ints(int *array, const char *string, const int arrayLength) {
  str_to_int_array(array, string, arrayLength);
  shift_array_centre(array, arrayLength);
  indmul_array(array, arrayLength);
  reverse_indmul_array(array, arrayLength);
}

