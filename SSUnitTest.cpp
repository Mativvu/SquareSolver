#include <stdio.h>
#include <float.h>
#include <math.h>
#include "SSStructures.h"
#include "SSUnitTest.h"
#include "SSInput.h"
#include "SSSolve.h"
#include "SSOutput.h"

const int MAXLEN = 100;
const double FLT_EPS = 1e8*FLT_EPSILON;
extern const char* ANSI_COLOR_GREEN;
extern const char* ANSI_COLOR_RED;
extern const char* ANSI_COLOR_RESET;

ExitCode RunUnitTests()
{
    FILE *fin_coeffs_p = fopen("UnitTestsInput", "r");
    FILE *fin_answers_p = fopen("UnitTestsAnswers", "r");

    int num_of_tests = 0;
    ExitCode status = FileInputNumOfTests(fin_coeffs_p, &num_of_tests);
    if (IsError(status))
    {
        return status;
    }

    for(int i = 0; i < num_of_tests; i++)
    {
        struct EquationCoeffs coeffs = {NAN, NAN, NAN};
        struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};
        struct EquationRoots answers = {NumOfRootsNAN, NAN, NAN};

        status = FileInputCoeffs(fin_coeffs_p, &coeffs);
        if (IsError(status))
        {
            printf("Error input coeffs test %d \n", i+1);
            return status;
        }

        status = FileInputTestAnswers(fin_answers_p, &answers);
        if (IsError(status))
        {
            printf("Error input ans test %d \n", i+1);
            return status;
        }

        status = SolveQuadEquation(&coeffs, &roots);
        if (IsError(status))
        {
            printf("Error solver test %d \n", i+1);
            return status;
        }

        if(!IsRootsEqual(&roots, &answers))
        {
            printf("Test %d failed \n", i+1);
            printf("Test coefficients: a = %lg, b = %lg, c = %lg \n",
                   coeffs.a, coeffs.b, coeffs.c);
            printf("Recieved values: nRoots = %d, x1 = %lg, x2 = %lg \n",
                   roots.num_of_roots, roots.x1, roots.x2);
            printf("Expected values: nRoots = %d, x1 = %lg, x2 = %lg \n",
                   answers.num_of_roots, answers.x1, answers.x2);
            return ExitCodeEND_TEST;
        }
    }

    COLOR_GREEN_printf("All tests passed! \n");

    fclose(fin_coeffs_p);
    fclose(fin_answers_p);
    return ExitCodeEND_TEST;
}

bool IsFloatsEqual(double a, double b)
{
    if(isnan(a) && isnan(b))
    {
        return true;
    }
    a = fabs(a), b = fabs(b);
    return (a >= (1-FLT_EPS)*b && a <= (1+FLT_EPS)*b);
}

bool IsRootsEqual(EquationRoots *roots1_ptr, EquationRoots *roots2_ptr)
{
    bool nRoots_equal = (roots1_ptr->num_of_roots == roots2_ptr->num_of_roots);
    bool x1_equal = IsFloatsEqual(roots1_ptr->x1, roots2_ptr->x1);
    bool x2_equal = IsFloatsEqual(roots1_ptr->x2, roots2_ptr->x2);
    return (nRoots_equal && x1_equal && x2_equal);
}
ExitCode FileInputTestAnswers(FILE *fin_answers_p, EquationRoots *answers_ptr)
{
    char line[MAXLEN] = {0};
    int num_of_inputted = 0; // res

    FileReadLine(fin_answers_p, line);
    num_of_inputted = sscanf(line, "%d %lg %lg", &answers_ptr->num_of_roots, &answers_ptr->x1, &answers_ptr->x2);
    if (num_of_inputted != answers_ptr->num_of_roots+1)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode FileInputNumOfTests(FILE *fin_coeffs_p, int *num_of_tests)
{
    char line[MAXLEN] = {0};

    FileReadLine(fin_coeffs_p, line);
    int res = sscanf(line, "%d", num_of_tests);
    if (res != 1)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}
