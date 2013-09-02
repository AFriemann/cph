/*
psafe main file, please read documentation for further information.
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


#ifndef PSAFE
#define PSAFE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

#include "psafeKey.h"
#include "psafeInputHandler.h"
#include "psafeClipboardHandler.h"

#define VERSION 0.9

#define MAX_INPUT_SIZE 64
#define MAX_KEY_SIZE 128
#define DEFAULT_KEY_SIZE 12

static int FLAG_PRINT = 0;

static char *profile;
static char *password;
static char *key_buffer;
static int key_size = DEFAULT_KEY_SIZE;

static const char *error_msg = "not enough arguments given! Try --help\n";
static const char *help_msg = "psafe returns a password for any given profile and password.\n"
                              "profile should be an easy to remember name for your password, can be provided later.\n"
                              "usage: psafe [OPTIONS] [profile]\n"
                              "\t-h, --help: show this help message\n"
                              "\t-l, --key-size: set key length, default is 12\n"
                              "\t-p, --password: set password\n"
                              "\t-c, --license: show license notice\n\n";

static const char *license =  "psafe  Copyright (C) 2013  Aljosha Friemann\n" 
                              "This program comes with ABSOLUTELY NO WARRANTY!\n"
                              "This is free software, and you are welcome to redistribute it\n"
                              "under certain conditions; please read the provided license file for details.\n";

static struct option long_options[] = {
  /* These options set a flag. */
  {"print-key",   no_argument,  &FLAG_PRINT, 1},
  /* These options don't set a flag.
    We distinguish them by their indices. */
  {"help",        no_argument,        0, 'h'},
  {"key-size",    required_argument,  0, 'l'},
  {"password",    required_argument,  0, 'p'},
  {"license",     no_argument,        0, 'c'},
  {"version",     no_argument,        0, 'v'},
  {0, 0, 0, 0}
};

void clear_buffers(void);
int main(int argc, char *argv[]);

#endif
