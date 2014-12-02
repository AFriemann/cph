/*
cph key algorithm header source, generates keys.
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

#ifndef CPH_KEY
#define CPH_KEY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gcrypt.h>

int generate_key(char *buffer, const char *profile, const char *password, const unsigned int length, const unsigned int algorithm, const unsigned int extended);

#endif
