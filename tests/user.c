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
#define TEST_SUITE_NAME "user"
#include "test_macros.h"





TEST_START(USER)

int isset;
fnasso_error error;
fnasso_context *tctx;
int msk_len = 64;
unsigned char *msk = malloc(64);
memset(msk, 'a', 64);
unsigned char *msk2 = malloc(64);
memset(msk2, 'b', 64);


fnasso_context_init(&tctx);

error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("a1");
if (isset) TEST_ERROR("a2");

error = fnasso_user_isset(NULL, &isset);
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("a3");

error = fnasso_user_isset(tctx, NULL);
if (error != FNASSO_ERR_OUTPUT_PTR_NULL) TEST_ERROR("a3");


fnasso_user_free(tctx);
error = fnasso_user_set_with_msk(tctx, msk, msk_len);
if (error) TEST_ERROR("b1");
if (!tctx->user) TEST_ERROR("b2");
if (!tctx->user->msk) TEST_ERROR("b3");
if (!tctx->user->msk->key) TEST_ERROR("b4");
if (!tctx->user->msk->len) TEST_ERROR("b5");
if (!tctx->user->name) TEST_ERROR("b6");
if (!tctx->user->password) TEST_ERROR("b7");
if (memcmp(msk, tctx->user->msk->key, msk_len)) TEST_ERROR("b8");
if (msk_len != tctx->user->msk->len) TEST_ERROR("b9");
if (strcmp("0098ba824b5c164", tctx->user->name)) TEST_ERROR("b10");
if (strcmp("AJi6gktcFkJ716ESKlpEKiXsZE0=", tctx->user->password)) TEST_ERROR("b11");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("b12");
if (!isset) TEST_ERROR("b13");

/////////////////////////////////////////////////////////////////////////////////////////

fnasso_context_set_roaming_realm(tctx, "skynet.com");

fnasso_user_free(tctx);
error = fnasso_user_set_with_msk(tctx, msk, msk_len);
if (error) TEST_ERROR("c1");
if (!tctx->user) TEST_ERROR("c2");
if (!tctx->user->msk) TEST_ERROR("c3");
if (!tctx->user->msk->key) TEST_ERROR("c4");
if (!tctx->user->msk->len) TEST_ERROR("c5");
if (!tctx->user->name) TEST_ERROR("c6");
if (!tctx->user->password) TEST_ERROR("c7");
if (memcmp(msk, tctx->user->msk->key, msk_len)) TEST_ERROR("c8");
if (msk_len != tctx->user->msk->len) TEST_ERROR("c9");
if (strcmp("0098ba824b5c164@skynet.com", tctx->user->name)) TEST_ERROR("c10");
if (strcmp("AJi6gktcFkJ716ESKlpEKiXsZE0=", tctx->user->password)) TEST_ERROR("c11");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("c12");
if (!isset) TEST_ERROR("c13");

/////////////////////////////////////////////////////////////////////////

fnasso_user_free(tctx);
error = fnasso_user_set_with_msk(tctx, NULL, msk_len);
if (error != FNASSO_ERR_NO_MSK) TEST_ERROR("d1");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("d2");
if (isset) TEST_ERROR("d3");

fnasso_user_free(tctx);
error = fnasso_user_set_with_msk(tctx, msk, 0);
if (error != FNASSO_ERR_NO_MSK) TEST_ERROR("d4");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("d5");
if (isset) TEST_ERROR("d6");

fnasso_user_free(tctx);
error = fnasso_user_set_with_msk(tctx, msk, -1);
if (error != FNASSO_ERR_NO_MSK) TEST_ERROR("d7");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("d8");
if (isset) TEST_ERROR("d9");

fnasso_user_free(tctx);
error = fnasso_user_set_with_msk(NULL, msk, msk_len);
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("d10");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("d11");
if (isset) TEST_ERROR("d12");

////////////////////////////////////////////////////////////////////

error = fnasso_user_set_with_msk(tctx, msk, msk_len);
if (error) TEST_ERROR("e1");
if (!tctx->user) TEST_ERROR("e2");
if (!tctx->user->msk) TEST_ERROR("e3");
if (!tctx->user->msk->key) TEST_ERROR("e4");
if (!tctx->user->msk->len) TEST_ERROR("e5");
if (!tctx->user->name) TEST_ERROR("e6");
if (!tctx->user->password) TEST_ERROR("e7");
if (memcmp(msk, tctx->user->msk->key, msk_len)) TEST_ERROR("e8");
if (msk_len != tctx->user->msk->len) TEST_ERROR("e9");
if (strcmp("0098ba824b5c164@skynet.com", tctx->user->name)) TEST_ERROR("e10");
if (strcmp("AJi6gktcFkJ716ESKlpEKiXsZE0=", tctx->user->password)) TEST_ERROR("e11");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("e12");
if (!isset) TEST_ERROR("e13");

fnasso_context_set_roaming_realm(tctx, NULL);
error = fnasso_user_set_with_msk(tctx, msk2, msk_len);
if (error) TEST_ERROR("f1");
if (!tctx->user) TEST_ERROR("f2");
if (!tctx->user->msk) TEST_ERROR("f3");
if (!tctx->user->msk->key) TEST_ERROR("f4");
if (!tctx->user->msk->len) TEST_ERROR("f5");
if (!tctx->user->name) TEST_ERROR("f6");
if (!tctx->user->password) TEST_ERROR("f7");
if (memcmp(msk2, tctx->user->msk->key, msk_len)) TEST_ERROR("f8");
if (msk_len != tctx->user->msk->len) TEST_ERROR("f9");
if (strcmp("9d682ff9a701860", tctx->user->name)) TEST_ERROR("f10");
if (strcmp("nWgv+acBhgMCMXa4wSkmxqFVEO4=", tctx->user->password)) TEST_ERROR("f11");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("f12");
if (!isset) TEST_ERROR("f13");

fnasso_context_set_roaming_realm(tctx, "hxe.com");
error = fnasso_user_set_with_msk(tctx, msk2, msk_len);
if (error) TEST_ERROR("g1");
if (!tctx->user) TEST_ERROR("g2");
if (!tctx->user->msk) TEST_ERROR("g3");
if (!tctx->user->msk->key) TEST_ERROR("g4");
if (!tctx->user->msk->len) TEST_ERROR("g5");
if (!tctx->user->name) TEST_ERROR("g6");
if (!tctx->user->password) TEST_ERROR("g7");
if (memcmp(msk2, tctx->user->msk->key, msk_len)) TEST_ERROR("g8");
if (msk_len != tctx->user->msk->len) TEST_ERROR("g9");
if (strcmp("9d682ff9a701860@hxe.com", tctx->user->name)) TEST_ERROR("g10");
if (strcmp("nWgv+acBhgMCMXa4wSkmxqFVEO4=", tctx->user->password)) TEST_ERROR("g11");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("g12");
if (!isset) TEST_ERROR("g13");


///////////////////////////////////////////////////////////////////////////

error = fnasso_user_set(tctx, "hanky@skynet.com", "1234");
if (error) TEST_ERROR("g1");
if (!tctx->user) TEST_ERROR("g2");
if (tctx->user->msk) TEST_ERROR("g3");
if (!tctx->user->name) TEST_ERROR("g4");
if (!tctx->user->password) TEST_ERROR("g5");
if (strcmp("hanky", tctx->user->name)) TEST_ERROR("g6");
if (strcmp("1234", tctx->user->password)) TEST_ERROR("g7");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("g8");
if (!isset) TEST_ERROR("g9");

//////////////////////////////////////////////////////

error = fnasso_user_set(tctx, "hanky@skynet.com", "");
if (error) TEST_ERROR("h1");
if (!tctx->user) TEST_ERROR("h2");
if (tctx->user->msk) TEST_ERROR("h3");
if (!tctx->user->name) TEST_ERROR("h4");
if (!tctx->user->password) TEST_ERROR("h5");
if (strcmp("hanky", tctx->user->name)) TEST_ERROR("h6");
if (strcmp("", tctx->user->password)) TEST_ERROR("h7");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("h8");
if (!isset) TEST_ERROR("h9");

//////////////////////////////////////////////////////

error = fnasso_user_set(tctx, "hanky@skynet.com", NULL);
if (error) TEST_ERROR("i1");
if (!tctx->user) TEST_ERROR("i2");
if (tctx->user->msk) TEST_ERROR("i3");
if (!tctx->user->name) TEST_ERROR("i4");
if (!tctx->user->password) TEST_ERROR("i5");
if (strcmp("hanky", tctx->user->name)) TEST_ERROR("i6");
if (strcmp("", tctx->user->password)) TEST_ERROR("i7");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("i8");
if (!isset) TEST_ERROR("i9");

//////////////////////////////////////////////////////


error = fnasso_user_set(tctx, NULL, "1234");
if (error != FNASSO_ERR_NO_USERNAME_SUPPLIED) TEST_ERROR("d1");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("j2");
if (isset) TEST_ERROR("j3");

error = fnasso_user_set(tctx, "", "1234");
if (error != FNASSO_ERR_NO_USERNAME_SUPPLIED) TEST_ERROR("j4");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("j5");
if (isset) TEST_ERROR("j6");

error = fnasso_user_set(tctx, "@skynet.com", "1234");
if (error != FNASSO_ERR_BADFORMED_KERBEROS_USERNAME) TEST_ERROR("j7");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("j8");
if (isset) TEST_ERROR("j9");

error = fnasso_user_set(NULL, "hanky@skynet.com", "1234");
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("j10");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("j11");
if (isset) TEST_ERROR("j12");

error = fnasso_user_set(NULL, "hanky@skynet.com", "1234");
if (error != FNASSO_ERR_NO_CONTEXT_SUPPLIED) TEST_ERROR("j13");
error = fnasso_user_isset(tctx, &isset);
if (error) TEST_ERROR("j14");
if (isset) TEST_ERROR("j15");

/////////////////////////////////////////////////////////

// Check for double free errors
fnasso_user_free(tctx);
fnasso_user_free(tctx);
fnasso_user_free(tctx);
fnasso_context_free(&tctx);
fnasso_context_free(&tctx);
fnasso_context_free(&tctx);
if (tctx) TEST_ERROR("x1");

free(msk);
free(msk2);

TEST_END()

int user()
{
	SUITE_START();

	RUN_TEST(USER);

	SUITE_END();
}


