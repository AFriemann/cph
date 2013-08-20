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


#ifndef ARRAY_OPERATIONS
#define ARRAY_OPERATIONS

#include <stdio.h>
#include "literalOperations.h"

void multiplicateArrayElements(int* array1, const int* array2, const int arraySize);
void arrayElementIndexMultiplication(int* array, const int arraySize);
void reverseArrayElementIndexMultiplication(int* array, const int arraySize);
void addArrayElements(int* array1, const int* array2, const int arraySize);
void shiftArrayCentre(int* array, const int arraySize);

#endif
