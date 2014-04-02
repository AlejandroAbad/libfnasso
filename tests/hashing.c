/*
 * File:   utils.c
 * Author: hanky
 *
 * Created on Mar 5, 2014, 7:09:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "../fnasso.h"
#include "../fnasso_defs.h"

#define TEST_SUITE_NAME "hashing"
#include "test_macros.h"


TEST_START(HASH)

char *output;
int l, i;

l = fnasso_hash("hola", 4, &output);
if (l != 20) TEST_ERROR("1");
if (!output) TEST_ERROR("2");
char result1[20] = {0x99, 0x80, 0x0b, 0x85, 0xd3, 0x38, 0x3e, 0x3a, 0x2f, 0xb4, 0x5e, 0xb7, 0xd0, 0x06, 0x6a, 0x48, 0x79, 0xa9, 0xda, 0xd0};
if (memcmp(output, result1, l)) TEST_ERROR("3");
free(output);

l = fnasso_hash("", 0, &output);
if (l != 20) TEST_ERROR("4");
if (!output) TEST_ERROR("5");
char result2[20] = {0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55, 0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09};
if (memcmp(output, result2, l)) TEST_ERROR("6");
free(output);

l = fnasso_hash("", 0, NULL);
if (l != -1) TEST_ERROR("7");

l = fnasso_hash(NULL, 4, NULL);
if (l != -1) TEST_ERROR("8");

l = fnasso_hash("hola", -1, &output);
if (l != -1) TEST_ERROR("9");

TEST_END()





int hashing()
{

	SUITE_START();

	RUN_TEST(HASH);

	SUITE_END();
}


