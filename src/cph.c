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
      init_buffer(&word, FALSE) &&
      init_buffer(&salt, FALSE) &&
      init_buffer(&key_buffer, TRUE);
}

int clear_buffers(void)
{
    return
      clear_buffer(&word) &&
      clear_buffer(&salt) &&
      clear_buffer(&key_buffer);
}

int main(int argc, char **argv)
{
    Config config;

    int RETVAL = EXIT_OK;

    if (init_buffers()) {
        config = parse_args(argc, argv, word, salt);

        while (!config.ERR) {
            if (!input(word, "word") || !input(salt, "salt")) {
                RETVAL = EXIT_INPUT_ERR;
                break;
            }

            RETVAL = generate_key(key_buffer, word, salt, config.LENGTH, config.ALGORITHM, config.EXTENDED);

            output(key_buffer);
            break;
        }

        clear_buffers();
        exit(RETVAL);
    }

    fputs("failed to allocate memory", stderr);
    exit(EXIT_MEM_ERR);
}
