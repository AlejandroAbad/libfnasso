/* 
 * File:   macros.h
 * Author: hanky
 *
 * Created on March 5, 2014, 7:20 PM
 */


#ifndef TEST_SUITE_NAME
#define TEST_SUITE_NAME "suit_name"
#endif

#ifndef MACROS_H
#define	MACROS_H

#define SUITE_START() \
	printf("%%SUITE_STARTING%% %s \n", TEST_SUITE_NAME);\
	printf("%%SUITE_STARTED%%\n")

#define TEST_START(name) \
        void _ ## name ## _test() {\
        char *test_name = #name;\
	printf("START %s %s\n", TEST_SUITE_NAME, #name);


#define TEST_END() \
        printf("STOP %s %s\n", TEST_SUITE_NAME, test_name);\
        }

#define TEST_ERROR(msg) \
        printf("%%TEST_FAILED%% time=0 testname=_%s_test (%s) message=%s\n", __FUNCTION__, TEST_SUITE_NAME, #msg)


#define RUN_TEST(name) \
	printf("%%TEST_STARTED%% %s (%s)\n", #name, TEST_SUITE_NAME);\
	_ ## name ## _test();\
	printf("%%TEST_FINISHED%% time=0 %s (%s) \n", #name, TEST_SUITE_NAME)



#define SUITE_END() \
	printf("%%SUITE_FINISHED%% time=0\n");\
        return (EXIT_SUCCESS);

#endif	/* MACROS_H */

