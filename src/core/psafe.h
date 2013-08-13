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
static int keySize;
static const int defaultKeySize = 12;
static const int maxPwdSize = 32;

static const char *passwordPrompt = "Please enter your password: ";
static const char *errorMsg = "not enough arguments given! Try --help\n";
static const char *helpMsg = "psafe returns a password for any two given profile and password.\
                              Current default key size is 12.\
                                  usage: psafe <profile> [key size]\n\
                                    \t-h, --help: show this help message";

static struct option long_options[] = {
  /* These options set a flag. */
  //{"print-key",       no_argument,  &FLAG_PRINT, 1},
  /* These options don't set a flag.
    We distinguish them by their indices. */
  //{"print-key",        no_argument,   0, 'p'},
  {"help",        no_argument,        0, 'h'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[]);

#endif
