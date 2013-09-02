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

#ifndef LITERAL_OPERATIONS
#define LITERAL_OPERATIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LITERAL_MIN 33
#define LITERAL_MAX 126

int lit_add(const int a, const int b);
int lit_sub(const int a, const int b);
int lit_mul(const int a, const int b);

void str_to_int_array(int *buffer, const char *str, const int array_size);
void int_array_to_str(char *buffer, const int *array, const int array_size);

#endif

