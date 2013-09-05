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

char
literal(const char c) {
  char result = c % LITERAL_MAX;

  if (result < 0)
    result += LITERAL_MAX;
  if (result < LITERAL_MIN)
    result += LITERAL_MIN;

  return result;
}

int 
lit_add(const int a, const int b) {
  int result = (a + b) % LITERAL_MAX;
  if (result < LITERAL_MIN)
    result += LITERAL_MIN;
  //printf("\t\t%i + %i = %i\n", a, b, result);
  return result;
}

int 
lit_sub(const int a, const int b) {
  int result = (a - b) % LITERAL_MAX;

  /* ensure values > 0 */
  if (result < 0)
    result += LITERAL_MAX;

  if (result < LITERAL_MIN)
    result += LITERAL_MIN;
  //printf("\t\t%i + %i = %i\n", a, b, result);
  return result;
}

int 
lit_mul(const int a, const int b) {
  int result = (a * b) % LITERAL_MAX;
  if (result < LITERAL_MIN)
    result += LITERAL_MIN;
  //printf("\t\t%i * %i = %i\n", a, b, result);
  return result;
}

