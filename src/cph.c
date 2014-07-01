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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>

// mlock: linux specific?
#include <sys/mman.h>

#include "argparse.h"
#include "cph_key.h"
#include "cph_input_handler.h"
#include "cph_clipboard_handler.h"

#define EXIT_OK 0
#define EXIT_MEM_ERR 1

static char *word;
static char *salt;
static int input_buffer_size;

static char *key_buffer;
static int output_buffer_size;

int init_buffers(void)
{
    input_buffer_size = INPUT_MAX * sizeof(char);
    output_buffer_size = OUTPUT_MAX * sizeof(char);
    word = malloc(input_buffer_size);
    salt = malloc(input_buffer_size);
    key_buffer = calloc(OUTPUT_MAX, sizeof(char));

    return (mlock(word, input_buffer_size) && mlock(salt, input_buffer_size) && mlock(key_buffer, output_buffer_size));
}

int clear_buffers(void)
{
    memset(word, 0, input_buffer_size);
    memset(salt, 0, input_buffer_size);
    memset(key_buffer, 0, output_buffer_size);
    free(word);
    free(salt);
    free(key_buffer);

    return (munlock(word, input_buffer_size) && munlock(salt, input_buffer_size) && munlock(key_buffer, output_buffer_size));
}

int main(int argc, char **argv)
{
    int RETVAL = EXIT_OK;

    if (!init_buffers()) {
        Config config = parse_args(argc, argv, word, salt);

        if (strlen(word) == 0) { get_input(word, "word", INPUT_MAX, config.GUI); }
        if (strlen(salt) == 0) { get_input(salt, "salt", INPUT_MAX, config.GUI); }

        RETVAL = generate_key(key_buffer, word, salt, config.LENGTH, config.ALGORITHM, config.EXTENDED);

        if (!config.GUI) {
            // print password if in tty and GUI option not set; TODO: working in terminal detection
            fprintf(stdout, "%s", key_buffer);
        }
        else {
            str_to_clipboard(key_buffer);
        }

        clear_buffers();
        exit(RETVAL);
    }

    fputs("failed to allocate memory", stderr);
    exit(EXIT_MEM_ERR);
}
