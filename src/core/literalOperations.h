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

#ifndef LITERALOPERATIONS
#define LITERALOPERATIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int literalAddition(const int a, const int b);
int literalSubtraction(const int a, const int b);
int literalMultiplication(const int a, const int b);

void writeStringToIntArray(int *buffer, const char *string, const int arraySize);
void writeIntArrayToString(char *buffer, const int *intArray, const int arraySize);

#endif

