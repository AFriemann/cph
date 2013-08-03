#ifndef PSAFE_KEY_TESTS
#define PSAFE_KEY_TESTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../core/psafeKey.h"

int cleanCreateKeyTest(int (*f)(char **stringBuffer), int bufferCount, int keyLength);

// createKey tests 
int keyLengthTest(char **stringBuffer);
void keyLengthTestWrapper(void);

int createKeyDifferentInputTest(char **stringBuffer);
void createKeyDifferentInputTestWrapper(void);

int createKeySameInputTest(char **stringBuffer);
void createKeySameInputTestWrapper(void);

int inputLongerThanOutputTest(char **stringBuffer);
void inputLongerThanOutputTestWrapper(void);

// Array modification tests
void addArrayElementsTest(void); 
void multiplicateArrayElementsTest(void); 
void arrayElementIndexMultiplicationTest(void); 

#endif
