#define _CRT_SECURE_NO_WARNINGS	
#include"Minunit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#define N 50
#define M 224
#define M_PI 3.14159265358979323846 
typedef enum { FALSE, TRUE }bool;



bool Test_ID(char* id)//return true if id has 9 nums 
{
	int idsize;
	idsize = strlen(id);
	if (idsize != 9)
		return FALSE;
	for (int i = 0; i < idsize; i++)
		if (id[i]<'0' || id[i]>'9')
			return FALSE;
	return TRUE;
}
bool Test_Move_Direction(int num)
{
	if (num == 0 || num == 1)
		return TRUE;
	return FALSE;
}
bool Test_Move_Size(int num)
{
	if (num > 0 && num < 6)
		return TRUE;
	return FALSE;
}
bool Test_Choose_Shot(int num)
{
	if (num < 1 || num>4)
		return FALSE;
	return TRUE;
}
bool Test_Angle_Shot(double num)
{
	if (num > 360 || num < 0)
		return FALSE;
	return TRUE;
}
bool Test_Power_Shot(double num)
{
	if (num < 1)
		return FALSE;
	return TRUE;
}
bool Test_Positive_Log(double num)
{
	if (num > 0)
		return TRUE;
	return FALSE;
}


static char * test_Test_Move_Direction()
{
	mu_assert("error, With Test_ID\n", Test_ID(123456789));
	return 0;
}

static char* test_Test_Move_Size()
{
	mu_assert("error, With Test_Move_Size \n", Test_Move_Size(1));
	return 0;
}
static char* test_Test_Choose_Shot()
{
	mu_assert("error, With Test_Choose_Shot \n", Test_Choose_Shot(4));
	return 0;
}
static char* test_Test_Angle_Shot()
{
	mu_assert("error, With Test_Angle_Shot \n", Test_Angle_Shot(30));
	return 0;
}
static char* testTest_Power_Shot()
{
	mu_assert("error, With Test_Power_Shot\n", Test_Power_Shot(100));
	return 0;
}
 
static char * all_tests() {
	mu_run_test(test_Test_ID);
	mu_run_test(test_Test_Move_Direction);
	mu_run_test(test_Test_Move_Size);
	mu_run_test(test_Test_Choose_Shot);
	mu_run_test(test_Test_Move_Size);
	mu_run_test(test_Test_Angle_Shot);
	mu_run_test(test_Test_Power_Shot);

	return 0;
}


void test()
{

	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);

	return result != 0;

}