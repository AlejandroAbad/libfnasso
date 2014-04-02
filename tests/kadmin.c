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

#define TEST_SUITE_NAME "kadmin"
#include "test_macros.h"


TEST_START(KADM_TEST)



TEST_END()


int kadmin()
{
    
    RUN_TEST(KADM_TEST);
    
    return (EXIT_SUCCESS);
}

