/*
cph input/output header file; used to handle user inputs.
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

#ifndef CPH_MEMORY
#define CPH_MEMORY

#ifdef __linux
#include <sys/mman.h>
#endif

#include "cph_io.h"

#define IO_MAX 32
#define BUFFER_SIZE (IO_MAX + 1) * sizeof (char)

int init_buffer(char **buffer, const unsigned int zero);
int clear_buffer(char **buffer);

#endif
