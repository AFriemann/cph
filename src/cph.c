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

unsigned int RETVAL = 0;

static char *word;
static char *salt;
static char *key_buffer;

void init_buffers(void)
{
    word = malloc(INPUT_MAX * sizeof(char));
    salt = malloc(INPUT_MAX * sizeof(char));
    key_buffer = calloc(OUTPUT_MAX, sizeof(char));
}

void clear_buffers(void)
{
    memset(word, 0, strlen (word) * sizeof(char));
    memset(salt, 0, strlen (salt) * sizeof(char));
    memset(key_buffer, 0, strlen (key_buffer) * sizeof(char));
    free(word);
    free(salt);
    free(key_buffer);
}

int main(int argc, char **argv)
{
    if (mlockall(MCL_FUTURE) == 0) {
        init_buffers();
        Namespace namespace = parse_args(argc, argv, word, salt);

        if (strlen(word) == 0) { get_input(word, "word", INPUT_MAX, namespace.GUI); }
        if (strlen(salt) == 0) { get_input(salt, "salt", INPUT_MAX, namespace.GUI); }

        if (!generate_key(key_buffer, word, salt, namespace.LENGTH, namespace.ALGORITHM, namespace.EXTENDED)) {
            RETVAL = 2;
        }
        else if (isatty(1) && !namespace.GUI) {
            // print password if in tty and GUI option not set; TODO: working in terminal detection
            fprintf(stdout, "%s\n", key_buffer);
        }
        else {
            str_to_clipboard(key_buffer);
        }

        clear_buffers();
        munlockall();
    } else {
        RETVAL = 1;
    }

    exit(RETVAL);
}
