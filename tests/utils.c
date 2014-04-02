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

#define TEST_SUITE_NAME "utils"
#include "test_macros.h"


TEST_START(SPLIT_NAME)
	  
	char *user, *realm;
	fnasso_error retval;
	
	retval = fnasso_split_name("user@realm.com", &user, &realm);
	if(retval)	TEST_ERROR("1");
	if(strcmp(user, "user")) TEST_ERROR("2");
	if(strcmp(realm, "realm.com")) TEST_ERROR("3");
	free(user);
	free(realm);
	
	retval = fnasso_split_name("user", &user, &realm);
	
	if(retval)	TEST_ERROR("4");
	if(strcmp(user, "user")) TEST_ERROR("5");
	if(strcmp(realm, "")) TEST_ERROR("6");
	free(user);
	free(realm);

	
	retval = fnasso_split_name("user", &user, NULL);
	
	if(retval)	TEST_ERROR("7");
	if(strcmp(user, "user")) TEST_ERROR("8");
	free(user);
	
	retval = fnasso_split_name("realm.com", NULL, &realm);
	
	if(retval)	TEST_ERROR("9");
	if(strcmp(realm, "realm.com")) TEST_ERROR("10");
	free(realm);
	
	retval = fnasso_split_name("user@realm.com", &user, NULL);
	if(retval)	TEST_ERROR("11");
	if(strcmp(user, "user")) TEST_ERROR("12");
	free(user);
	
	retval = fnasso_split_name("user@realm.com", NULL, NULL);
	if (retval) TEST_ERROR("13");
	
	retval = fnasso_split_name("@realm.com", &user, &realm);
	if (retval != FNASSO_ERR_BADFORMED_KERBEROS_USERNAME) TEST_ERROR("14");
	
	retval = fnasso_split_name("user@", &user, &realm);
	if (retval != FNASSO_ERR_BADFORMED_KERBEROS_USERNAME) TEST_ERROR("15");	

	retval = fnasso_split_name("", &user, &realm);
	if(retval != FNASSO_ERR_NO_USERNAME_SUPPLIED)	TEST_ERROR("16");

	retval = fnasso_split_name(NULL, &user, &realm);
	if(retval != FNASSO_ERR_NO_USERNAME_SUPPLIED)	TEST_ERROR("17");	

	
TEST_END()





int utils()
{
	SUITE_START();
	
	
	RUN_TEST(SPLIT_NAME);
	
	
	
	SUITE_END();
}
