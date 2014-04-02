/*
 * File:   utils.c
 * Author: hanky
 *
 * Created on Mar 5, 2014, 7:09:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../fnasso.h"
#include "../fnasso_defs.h"

#define TEST_SUITE_NAME "kdc"
#include "test_macros.h"


TEST_START(KDC)

int time;
fnasso_error error;
fnasso_context *tctx;
int msk_len = 64;
unsigned char *msk = malloc(64);
memset(msk, 'a', 64);
unsigned char *msk2 = malloc(64);
memset(msk2, 'b', 64);
fnasso_context_init(&tctx);

/////////////////////////////////////////////////////////

error = fnasso_kdc_get_tgt(NULL, NULL);
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("a1");

error = fnasso_kdc_get_tgt(tctx, NULL);
if (error != FNASSO_ERR_USER_DATA_NOT_SET) TEST_ERROR("a2");

error = fnasso_kdc_get_tgt(NULL, &time);
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("a3");

error = fnasso_kdc_get_tgt(tctx, &time);
if (error != FNASSO_ERR_USER_DATA_NOT_SET) TEST_ERROR("a4");

////////////////////////////////////////////////////////////

error = fnasso_kdc_check_tgt(NULL, NULL);
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("b1");

error = fnasso_kdc_check_tgt(tctx, NULL);
if (error != FNASSO_ERR_OUTPUT_PTR_NULL) TEST_ERROR("b2");

error = fnasso_kdc_check_tgt(NULL, &time);
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("b3");

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("b4");
if (time != -1) TEST_ERROR("b5");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "nonexistentuser@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "nonexistentkerberosrealm.com");

error = fnasso_kdc_get_tgt(tctx, &time);
if (error != FNASSO_ERR_EXTERNAL) TEST_ERROR("c1");

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("c2");
if (time != -1) TEST_ERROR("c3");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "nonexistentuser@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "hxe.com");

error = fnasso_kdc_get_tgt(tctx, &time);
if (error != FNASSO_ERR_EXTERNAL) TEST_ERROR("d1");

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("d2");
if (time != -1) TEST_ERROR("d3");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "pepe@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "hxe.com");

fnasso_kdc_free(tctx);
error = fnasso_kdc_get_tgt(tctx, &time);
if (error) TEST_ERROR("e1");
if (time != 36000 && time != 36000+1 && time != 36000-1) TEST_ERROR("e2");

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("e3");
if (time != 36000 && time != 36000+1 && time != 36000-1) TEST_ERROR("e4");

sleep(1);

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("e5");
if (time != 36000-1 && time != 36000 && time != 36000-2) TEST_ERROR("e6");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "nonexistentuser@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "hxe.com");

error = fnasso_kdc_get_tgt(tctx, &time);
if (error != FNASSO_ERR_EXTERNAL) TEST_ERROR("f1");

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("f2");
if (time != -1) TEST_ERROR("f3");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "pepe@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "hxe.com");

fnasso_kdc_free(tctx);
error = fnasso_kdc_get_tgt(tctx, &time);
if (error) TEST_ERROR("g1");
if (time != 36000 && time != 36000+1 && time != 36000-1) TEST_ERROR("g2");

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("g3");
if (time != 36000 && time != 36000+1 && time != 36000-1) TEST_ERROR("g4");

sleep(1);

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("g5");
if (time != 36000-1 && time != 36000 && time != 36000-2) TEST_ERROR("g6");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "pepe@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "hxe.com");
fnasso_context_set_cache_name(tctx, "FILE:/root/where_is_not_allowed");

fnasso_kdc_free(tctx);
error = fnasso_kdc_get_tgt(tctx, &time);
if (error != FNASSO_ERR_EXTERNAL) TEST_ERROR("h1");

error = fnasso_kdc_check_tgt(tctx, &time);
if (error) TEST_ERROR("h3");
if (time != -1) TEST_ERROR("h4");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "pepe@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "hxe.com");
fnasso_context_set_cache_name(tctx, NULL);

fnasso_kdc_free(tctx);
error = fnasso_kdc_get_tgt(tctx, &time);
if (error) TEST_ERROR("i1");
if (time != 36000 && time != 36000+1 && time != 36000-1) TEST_ERROR("i2");

/////////////////////////////////////////////////////////

fnasso_user_set(tctx, "pepe@hxe.com", "1234");
fnasso_context_set_roaming_realm(tctx, "hxe.com");
fnasso_context_set_cache_name(tctx, "FILE:/tmp/fnasso_krb5cc");

fnasso_kdc_free(tctx);
error = fnasso_kdc_get_tgt(tctx, &time);
if (error) TEST_ERROR("j1");
if (time != 36000 && time != 36000+1 && time != 36000-1) TEST_ERROR("j2");

/////////////////////////////////////////////////////////

// Check for double free errors
fnasso_kdc_free(tctx);
fnasso_kdc_free(tctx);
fnasso_kdc_free(tctx);
fnasso_context_free(&tctx);
fnasso_context_free(&tctx);
fnasso_context_free(&tctx);
if (tctx) TEST_ERROR("x1");

free(msk);
free(msk2);

TEST_END()







int kdc()
{
	SUITE_START();
	RUN_TEST(KDC);
	SUITE_END();
}



