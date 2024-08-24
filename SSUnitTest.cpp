#include <stdio.h>
#include <float.h>
#include <math.h>
#include "SSStructures.h"
#include "SSUnitTest.h"
#include "SSInput.h"
#include "SSSolve.h"
#include "SSOutput.h"
#include "SSDebug.h"

const double FLT_EPS = 1e8*FLT_EPSILON;

static EquationCoeffs test_inputs[] = {
    {2, -5, 3},
    {1.2, -7.8, 30},
    {1, -6, 9},
    {0.0002, -0.005, 0.005},
    {2, 128, 0},
    {2.45, 12.348, 3.234},
    {1, 0, -87.02932},
    {65.039, -5.3218, 3000},
    {2, -0.2636, 0.00868562}
};

#define ANSWER(num, x1, x2) {(NumOfRoots)(num), x1, x2}
static EquationRoots test_answers[] = {
    ANSWER(2, 1.5, 1),
    ANSWER(0, NAN, NAN),
    ANSWER(1, 3, NAN),
    ANSWER(2, 23.9564392373896, 1.043560762610399),
    ANSWER(2, 0, -64),
    ANSWER(2, -0.27714467697981027, -4.762855323020189),
    ANSWER(2, 9.328950638, -9.328950638),
    ANSWER(0, NAN, NAN),
    ANSWER(1, 0.0659, NAN)
};

ExitCode RunUnitTests()
{
    ColorPrintf(GREEN, "Starting testing\n");
    ColorPrintf(GREEN, "--------------------------------------\n");

    int failed = 0;
    int num_of_tests = (int) (sizeof(test_inputs)/sizeof(test_inputs[0]));
    for(int i = 0; i < num_of_tests; i++)
    {
        struct EquationCoeffs coeffs = test_inputs[i];
        struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};
        struct EquationRoots answers = test_answers[i];

        ExitCode status = SolveQuadEquation(&coeffs, &roots);
        if (IsError(status))
        {
            ColorPrintf(RED, "Error solver test %d \n", i+1);
            return status;
        }

        if (!IsRootsEqual(&roots, &answers))
        {
            ColorPrintf(RED, "Test %d failed \n", i+1);
            ColorPrintf(RED, "Test coefficients: a = %lg, b = %lg, c = %lg \n",
                        coeffs.a, coeffs.b, coeffs.c);
            ColorPrintf(RED, "Recieved values: nRoots = %d, x1 = %lg, x2 = %lg \n",
                        roots.num_of_roots, roots.x1, roots.x2);
            ColorPrintf(RED, "Expected values: nRoots = %d, x1 = %lg, x2 = %lg \n",
                        answers.num_of_roots, answers.x1, answers.x2);
            failed++;
        }
        else
        {
            ColorPrintf(GREEN, "Test %d passed\n", i+1);
        }
    }
    ColorPrintf(GREEN, "--------------------------------------\n");
    ColorPrintf(GREEN, "Tests passed %d\n", num_of_tests-failed);
    ColorPrintf(RED, "Test failed %d\n", failed);

    double percent = ((failed == 0) ? 100 : (100*(num_of_tests-failed))/num_of_tests);
    ColorPrintf(YELLOW, "Percentage of passed: %lg\n", percent);

    return ExitCodeEND_TEST;
}

bool IsFloatsEqual(double a, double b)
{
    if (isnan(a) && isnan(b))
    {
        return true;
    }
    a = fabs(a), b = fabs(b);
    return (a >= (1-FLT_EPS)*b && a <= (1+FLT_EPS)*b);
}

bool IsRootsEqual(EquationRoots *roots1_ptr, EquationRoots *roots2_ptr)
{
    DEBUGMyAssert(roots1_ptr != nullptr);
    DEBUGMyAssert(roots2_ptr != nullptr);

    bool nRoots_equal = (roots1_ptr->num_of_roots == roots2_ptr->num_of_roots);
    bool x1_equal = IsFloatsEqual(roots1_ptr->x1, roots2_ptr->x1);
    bool x2_equal = IsFloatsEqual(roots1_ptr->x2, roots2_ptr->x2);

    return (nRoots_equal && x1_equal && x2_equal);
}

ExitCode FileInputTestAnswers(FILE *fin_answers_p, EquationRoots *answers_ptr)
{
    DEBUGMyAssert(fin_answers_p != nullptr);
    DEBUGMyAssert(answers_ptr != nullptr);

    char line[MAXLEN] = {0};

    FileReadLine(fin_answers_p, line);
    int res = sscanf(line, "%d %lg %lg", &answers_ptr->num_of_roots, &answers_ptr->x1, &answers_ptr->x2);
    if (res != answers_ptr->num_of_roots+1)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode FileInputNumOfTests(FILE *fin_coeffs_p, int *num_of_tests)
{
    DEBUGMyAssert(fin_coeffs_p != nullptr);

    char line[MAXLEN] = {0};

    FileReadLine(fin_coeffs_p, line);
    int res = sscanf(line, "%d", num_of_tests);
    if (res != 1)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode FileRunUnitTests()
{
    FILE *fin_coeffs_p = fopen("UnitTestsInput.txt", "r");
    FILE *fin_answers_p = fopen("UnitTestsAnswers.txt", "r");
    if (fin_coeffs_p == nullptr || fin_answers_p == nullptr)
    {
        return ExitCodeFILE_ERROR;
    }

    int num_of_tests = 0;
    ExitCode status = FileInputNumOfTests(fin_coeffs_p, &num_of_tests);
    if (IsError(status))
    {
        return status;
    }

    ColorPrintf(GREEN, "Starting testing\n");
    ColorPrintf(GREEN, "--------------------------------------\n");
    int failed = 0;
    for (int i = 0; i < num_of_tests; i++)
    {
        struct EquationCoeffs coeffs = {NAN, NAN, NAN};
        struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};
        struct EquationRoots answers = {NumOfRootsNAN, NAN, NAN};

        status = FileInputCoeffs(fin_coeffs_p, &coeffs);
        if (IsError(status))
        {
            ColorPrintf(RED, "Error input coeffs test %d \n", i+1);
            return status;
        }

        status = FileInputTestAnswers(fin_answers_p, &answers);
        if (IsError(status))
        {
            ColorPrintf(RED, "Error input answer test %d \n", i+1);
            return status;
        }

        status = SolveQuadEquation(&coeffs, &roots);
        if (IsError(status))
        {
            ColorPrintf(RED, "Error solver test %d \n", i+1);
            return status;
        }

        if (!IsRootsEqual(&roots, &answers))
        {
            ColorPrintf(RED, "Test %d failed \n", i+1);
            ColorPrintf(RED, "Test coefficients: a = %lg, b = %lg, c = %lg \n",
                   coeffs.a, coeffs.b, coeffs.c);
            ColorPrintf(RED, "Recieved values: nRoots = %d, x1 = %lg, x2 = %lg \n",
                   roots.num_of_roots, roots.x1, roots.x2);
            ColorPrintf(RED, "Expected values: nRoots = %d, x1 = %lg, x2 = %lg \n",
                   answers.num_of_roots, answers.x1, answers.x2);
            failed++;
        }
        else
        {
            ColorPrintf(GREEN, "Test %d passed\n", i+1);
        }
    }
    ColorPrintf(GREEN, "--------------------------------------\n");
    ColorPrintf(GREEN, "Tests passed %d\n", num_of_tests-failed);
    ColorPrintf(RED, "Test failed %d\n", failed);
    double percent = ((failed == 0) ? 100 : (100*(num_of_tests-failed))/num_of_tests);
    ColorPrintf(YELLOW, "Percentage of passed: %lg\n", percent);

    fclose(fin_coeffs_p);
    fclose(fin_answers_p);
    return ExitCodeEND_TEST;
}
