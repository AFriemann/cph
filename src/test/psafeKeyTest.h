#ifndef PSAFE
#define PSAFE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../core/psafeKey.h"

static char **bufferArray;

int init_suite1(void);
int clean_suite1(void);
int main();

int cleanCreateKeyTest(int (*f)(void), int bufferCount);

// Tests
int keyLengthTest(void);
void keyLengthTestWrapper(void);

int createKeyDifferentInputTest(void);
void createKeyDifferentInputTestWrapper(void);

int createKeySameInputTest(void);
void createKeySameInputTestWrapper(void);

int inputLongerThanOutputTest(void);
void inputLongerThanOutputTestWrapper(void);

#endif
