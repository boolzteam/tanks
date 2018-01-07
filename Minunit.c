/*
 * TEAM BOOL - Z (17)  unit testing
 */


#define _CRT_SECURE_NO_WARNINGS
#include"header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <malloc.h>
#include <math.h>
#define N 50


typedef enum { FALSE, TRUE }bool;
int tests_run = 0;


bool Test_open_file();
bool Test_ID(char id[N]);
bool Test_Move_Direction(int num);
bool Test_Move_Size(int num);
bool Test_Choose_Shot(int num);
bool Test_Angle_Shot(double num);
bool Test_Power_Shot(double num);
bool Test_Positive_Log(double num);
bool Test_check_two_nums(int num1);
static char * test_Test_Move_Direction();
static char* test_Test_Move_Size();
static char* test_Test_Choose_Shot();
static char* test_Test_Angle_Shot();
static char * all_tests();






int main(int argc, char **argv)
{
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}


bool Test_check_two_nums(int num1)
{
  if (num1==0 || num1==1)
      return TRUE;
}
bool Test_ID(char id[N])//return true if id has 9 nums
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
bool Test_open_file()
{
    FILE *fout = NULL;
    fout=fopen("stam","w");
    if (fout==NULL)
    {
        fclose(fout);
        return FALSE;
    }
    fclose(fout);
    return TRUE;

}
static char * test_Test_open_file()
{
    mu_assert("error, With Test_open_file\n", Test_open_file());
    return 0;
}

static char * test_Test_check_two_nums()
{
    mu_assert("error, With Test_check_two_nums\n", Test_check_two_nums(0));
    return 0;
}

static char * unit_test_malloc() {
    char *pointer = NULL;
    pointer = (char*)malloc(1024);
    mu_assert("Error, not allocated dynamic string", pointer);
    return 0;
}

static char * unit_test_free() {
    char *pointer = NULL;
    pointer = (char*)malloc(1024);
    if (pointer != NULL)
    {
        free(pointer);
        pointer = NULL;
    }
    mu_assert("Error, did not free the pointer",pointer==NULL);
    return 0;
}


static char * test_Test_ID()
{
	mu_assert("error, With Test_ID\n", Test_ID("123456789"));
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
static char* test_Test_Power_Shot() {
    mu_assert("error, With Test_Power_Shot\n", Test_Power_Shot(100));
    return 0;

}
static char* test_Test_Move_Direction() {
    mu_assert("error, With Test_Move_Direction\n", Test_Move_Direction(1));
    return 0;

}
static char* test_Test_Positive_Log() {
    mu_assert("error, With Test_Positive_Log\n", Test_Positive_Log(2));
    return 0;

}


static char * all_tests()
{
	mu_run_test(test_Test_ID);
	mu_run_test(test_Test_Move_Direction);
	mu_run_test(test_Test_Move_Size);
	mu_run_test(test_Test_Choose_Shot);
	mu_run_test(test_Test_Angle_Shot);
	mu_run_test(test_Test_Power_Shot);
    mu_run_test(test_Test_Positive_Log);
    mu_run_test(unit_test_malloc);
    mu_run_test(unit_test_free);
    mu_run_test(test_Test_check_two_nums);
    mu_run_test(test_Test_open_file);


    return 0;
}


