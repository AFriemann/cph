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

static int FLAG_ERROR = 0;

static char *profile;
static char *password;
static int keySize;
static const int defaultKeySize = 12;
static const int maxPwdSize = 32;

static const char *errorMsg = "not enough arguments given! Try --help\n";
static const char *helpMsg = "psafe returns a password for any given profile and password.\n"
                              "profile should be an easy to remember name for your password, the key size is optional; the current default is 12.\n"
                              "\tusage: psafe <profile> <password> [key size]\n"
                              "\t-h, --help: show this help message\n";

static struct option long_options[] = {
  /* These options set a flag. */
  //{"print-key",       no_argument,  &FLAG_PRINT, 1},
  /* These options don't set a flag.
    We distinguish them by their indices. */
  {"help",        no_argument,        0, 'h'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[]);

#endif
