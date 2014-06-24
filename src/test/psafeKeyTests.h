#ifndef PSAFE_KEY_TESTS
#define PSAFE_KEY_TESTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../core/psafeKey.h"

int cleanCreateKeyTest(int (*f)(char **stringBuffer), int bufferCount, int keyLength);

// create_key tests 
int keyLengthTest(char **stringBuffer);
void keyLengthTestWrapper(void);

int create_keyDifferentInputTest(char **stringBuffer);
void create_keyDifferentInputTestWrapper(void);

int create_keySameInputTest(char **stringBuffer);
void create_keySameInputTestWrapper(void);

int inputLongerThanOutputTest(char **stringBuffer);
void inputLongerThanOutputTestWrapper(void);

void conv_string_to_intsTest(void);

#endif
