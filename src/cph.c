/*
cph main file, please read documentation for further information.
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

#include "cph.h"

int init_buffers(void)
{
    return
      init_buffer(word, 0) &&
      init_buffer(salt, 0) &&
      init_buffer(key_buffer, 1);
}

int clear_buffers(void)
{
    return
      clear_buffer(word) &&
      clear_buffer(salt) &&
      clear_buffer(key_buffer);
}

int main(int argc, char **argv)
{
    int RETVAL = EXIT_OK;

    if (init_buffers()) {
        Config config = parse_args(argc, argv, word, salt);

        if (strlen(word) == 0) { input(word, "word"); }
        if (strlen(salt) == 0) { input(salt, "salt"); }

        RETVAL = generate_key(key_buffer, word, salt, config.LENGTH, config.ALGORITHM, config.EXTENDED);

        output(key_buffer);

        clear_buffers();
        exit(RETVAL);
    }

    fputs("failed to allocate memory", stderr);
    exit(EXIT_MEM_ERR);
}
