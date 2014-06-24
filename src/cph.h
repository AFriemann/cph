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


#ifndef CPH_MAIN
#define CPH_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <gcrypt.h>

#include "cph_key.h"
#include "cph_input_handler.h"
#include "cph_clipboard_handler.h"

#define INPUT_MAX 64
#define KEY_MAX 128
#define DEFAULT_KEY_SIZE 12
#define REPS_DEFAULT 20000

const static char *VERSION = "1.3.1";

enum hash_algorithm {
  tiger = GCRY_MD_TIGER,
  tiger1 = GCRY_MD_TIGER1,
  tiger2 = GCRY_MD_TIGER2,
  sha256 = GCRY_MD_SHA256,
  sha512 = GCRY_MD_SHA512,
  whirlpool = GCRY_MD_WHIRLPOOL,
};

extern int max_input_length;

static int FLAG_PRINT = 0;
static int FLAG_EXT = 0;
static int FLAG_GUI = 0;

static char *profile;
static char *password;
static char *key_buffer;
static int key_size = DEFAULT_KEY_SIZE;

enum hash_algorithm h_algo = whirlpool;
static int h_reps = REPS_DEFAULT;

static const char *error_msg = "not enough arguments given! Try --help\n";
static const char *help_msg = "cph returns a password for any given profile and password.\n"
                              "profile should be an easy to remember name for your password, can be provided later.\n"
                              "usage: cph [OPTIONS] [profile]\n"
                              "\t-a, --algorithm    set hash algorithm, see readme for available options\n"
                              "\t-c, --license      show license notice\n"
                              "\t-e, --extended     use extended alphabet\n"
                              "\t-h, --help         show this help message\n"
                              "\t-l, --key-size     set key length to N, default is 12\n"
                              "\t-p, --password     set password to x (only for testing purposes!)\n"
                              "\t--print-key        print the key to stdout\n"
                              "\t-r, --repetitions  set number of repetitions; default is 20000";

static const char *license =  "cph  Copyright (C) 2013  Aljosha Friemann\n" 
                              "This program comes with ABSOLUTELY NO WARRANTY!\n"
                              "This is free software, and you are welcome to redistribute it\n"
                              "under certain conditions; please read the provided license file for details.";

static struct option long_options[] = {
  /* These options set a flag. */
  {"print-key",   no_argument,  &FLAG_PRINT, 1},
  /* These options don't set a flag.
    We distinguish them by their indices. */
  {"with-gui",    no_argument,        0, 'g'},
  {"algorithm",   required_argument,  0, 'a'},
  {"extended",    required_argument,  0, 'e'},
  {"license",     no_argument,        0, 'c'},
  {"help",        no_argument,        0, 'h'},
  {"key-size",    required_argument,  0, 'l'},
  {"password",    required_argument,  0, 'p'},
  {"repetitions", required_argument,  0, 'r'},
  {"version",     no_argument,        0, 'v'},
  {0, 0, 0, 0}
};

void clear_buffers(void);
int main(int argc, char *argv[]);

#endif
