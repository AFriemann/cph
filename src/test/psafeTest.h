#ifndef PSAFE
#define PSAFE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../core/psafeKey.h"

int init_suite1(void);
int clean_suite1(void);
int main();

// Tests
void differentInputShouldCreateDifferentKey(void);
void sameInputShouldCreateSameKey(void);
void createDbTest(void);
void encryptDbTest(void);

#endif
