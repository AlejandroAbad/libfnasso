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

#define TEST_SUITE_NAME "encoding"
#include "test_macros.h"


TEST_START(BASE64)

char *output;
int l;

l = fnasso_base64_encode("hola", 4, &output);
if (!output) TEST_ERROR("1");
if (strcmp(output, "aG9sYQ==")) TEST_ERROR("2");
if (l != 8) TEST_ERROR("3");
free(output);

l = fnasso_base64_encode("BIO_f_base64() returns the base64 BIO method. This is a filter", 62, &output);
if (!output) TEST_ERROR("4");
if (strcmp(output, "QklPX2ZfYmFzZTY0KCkgcmV0dXJucyB0aGUgYmFzZTY0IEJJTyBtZXRob2QuIFRoaXMgaXMgYSBmaWx0ZXI=")) TEST_ERROR("5");
if (l != 84) TEST_ERROR("6");
free(output);

l = fnasso_base64_encode("", 0, &output);
if (!output) TEST_ERROR("4");
if (strcmp(output, "")) TEST_ERROR("7");
if (l != 0) TEST_ERROR("8");
free(output);

l = fnasso_base64_encode("hola", 4, NULL);
if (l != -1) TEST_ERROR("9");

l = fnasso_base64_encode("hola", -1, NULL);
if (l != -1) TEST_ERROR("10");

l = fnasso_base64_encode(NULL, 4, &output);
if (l != 0) TEST_ERROR("11");
free(output);

TEST_END()



TEST_START(HEXSTR)

char *output;
int l;

l = fnasso_hexstr_encode("hola", 4, &output);
if (!output) TEST_ERROR("1");
if (strcmp(output, "686f6c61")) TEST_ERROR("2");
if (l != 8) TEST_ERROR("3");
free(output);


l = fnasso_hexstr_encode("", 0, &output);
if (!output) TEST_ERROR("4");
if (strcmp(output, "")) TEST_ERROR("5");
if (l != 0) TEST_ERROR("6");
free(output);

l = fnasso_hexstr_encode("hola", 4, NULL);
if (l != -1) TEST_ERROR("9");

l = fnasso_hexstr_encode("hola", -1, NULL);
if (l != -1) TEST_ERROR("10");

l = fnasso_hexstr_encode(NULL, 4, &output);
if (l != 0) TEST_ERROR("11");
free(output);
	
TEST_END()




int encoding()
{
	
	SUITE_START();

	RUN_TEST(BASE64);
	RUN_TEST(HEXSTR);
	
	SUITE_END();
}


