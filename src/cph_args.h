/*
cph args header file, please read documentation for further information.
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

#ifndef CPH_ARGS
#define CPH_ARGS

#include <getopt.h>
#include <stdio.h>

#include "cph_io.h"
#include "cph_key.h"

#define VERSION "1.5.3"

// Config struct for parsed arguments
typedef struct
{
    unsigned int ERR;
    unsigned int PRINT;
    unsigned int EXTENDED;
    unsigned int LENGTH;
    unsigned int ALGORITHM;
} Config;

static const char *error_msg = "not enough arguments given! Try --help\n";
static const char *help_msg = "cph returns a hash for any given word and salt.\n"
                              "usage: cph [OPTIONS]\n"
                              "\t-h, --help         show this help message\n"
                              "\t-c, --license      show license notice\n"
                              "\t-v, --version      show version\n"
                              "\t-a, --algorithm X  set hash algorithm, see readme for available options\n"
                              "\t-e, --extended     use baseE91 instead of base64\n"
                              "\t-l, --length N     set password length, default is 12\n"
                              "\n"
                              "input switches:\n"
                              "\t-w, --word W\n"
                              "\t-s, --salt S\n";

static const char *license =  "cph  Copyright (C) 2013  Aljosha Friemann\n" 
                              "This program comes with ABSOLUTELY NO WARRANTY!\n"
                              "This is free software, and you are welcome to redistribute it\n"
                              "under certain conditions; please read the provided license file for details.";

static struct option long_options[] = {
    /* These options set a flag. */
    /* These options don't set a flag. We distinguish them by their indices. */
    {"help",        no_argument,        0, 'h'},
    {"license",     no_argument,        0, 'c'},
    {"version",     no_argument,        0, 'v'},
    {"algorithm",   required_argument,  0, 'a'},
    {"extended",    no_argument,        0, 'e'},
    {"length",      required_argument,  0, 'l'},
    {"salt",        required_argument,  0, 's'},
    {"word",        required_argument,  0, 'w'},
    {0, 0, 0, 0}
};

unsigned int parse_algo(char *arg);
Config parse_args(int argc, char *argv[], char *word, char *salt);

#endif
