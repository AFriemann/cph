/*
cph input/output file; used to handle user inputs.
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

#include "cph_memory.h"

#ifdef __linux

/**
 * This method will allocate memory (which can be set to 0 if zero != 0) and
 * lock the buffer in ram.
 */
int init_buffer(char **buffer, const unsigned int zero)
{
    if (zero) {
        // TODO this is ugly..
        *buffer = calloc(IO_MAX + 1, sizeof(char));
    } else {
        *buffer = malloc(BUFFER_SIZE);
    }

    // mlock returns zero on success, therefore negated return
    return !mlock(*buffer, BUFFER_SIZE);
}

/**
 * This method will set buffer content to 0 and then free and unlock it.
 */
int clear_buffer(char **buffer)
{
    if (buffer == NULL) {
        return false;
    }

    memset(*buffer, 0, BUFFER_SIZE);
    free(*buffer);

    // munlock returns zero on success, therefore negated return
    return !munlock(*buffer, BUFFER_SIZE);
}

#else
#error Platform not supported
#endif
