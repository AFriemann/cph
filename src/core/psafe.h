#ifndef PSAFE
#define PSAFE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "psafeKey.h"



static int FLAG_PRINT = 0;
static int FLAG_PWDFROMFILE = 0;

static FILE *file;
static char *configFile = "/home/TODOSERNAME/.psafe"; //TODO

static char *profile;
static int keySize;
static const int maxParamSize = 64;

static const char *passwordPrompt = "Please enter your password: ";
static const char *errorMsg = "not enough arguments given! Try --help\n";
static const char *helpMsg = "psafe returns a password for any two given profile and password.\
                                  usage: psafe [OPTION] <profile> [key size]\n\
                                    \t-c, --config: run configuration wizard\
                                    \t-h, --help: show this help message\
                                    \t-p, --print: print key instead of writing it to the clipboard";

static struct option long_options[] = {
  /* These options set a flag. */
  {"print-key",       no_argument,  &FLAG_PRINT, 1},
  {"stored-pass",     no_argument,  &FLAG_PWDFROMFILE, 1}, // also p
  /* These options don't set a flag.
    We distinguish them by their indices. */
  {"help",        no_argument,        0, 'h'},
  {"configure",   no_argument,        0, 'c'},
  {"file",        required_argument,  0, 'f'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[]);

int readKeySizeFromFile(FILE *file);
char* readProfileFromFile(FILE *file);
char* readPassFromFile(FILE *file);

void keyToClipboard(char* key);

void configWizard(void);

#endif
