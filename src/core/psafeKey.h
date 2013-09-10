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

#ifndef PSAFE_KEY
#define PSAFE_KEY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gcrypt.h>

#define LITERAL_MAX 126
#define LITERAL_MIN 33

char literal(const char c);

void generate_key(char *buffer, const char *profile, const char *password, const int keySize, const unsigned int algorithm, const int reps);

#endif
