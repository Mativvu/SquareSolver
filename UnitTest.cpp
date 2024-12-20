#include <stdio.h>
#include <float.h>
#include <math.h>

#include "Structures.h"
#include "UnitTest.h"
#include "Input.h"
#include "Solve.h"
#include "Output.h"
#include "Debug.h"

const double FLT_EPS = 1e8 * FLT_EPSILON;

static EquationCoeffs test_inputs[] = {
//   a        b         c
    {2,       -5,       3           },
    {1.2,     -7.8,     30          },
    {1,       -6,       9           },
    {0.0002,  -0.005,   0.005       },
    {2,       128,      0           },
    {2.45,    12.348,   3.234       },
    {1,       0,        -87.02932   },
    {65.039,  -5.3218,  3000        },
    {2,       -0.2636,  0.00868562  }
};

#define ANSWER_LOCAL(num, x1, x2) {(NumOfRoots)(num), x1, x2}

static EquationRoots test_answers[] = {
//            nRoots    x1                     x2
    ANSWER_LOCAL(2,     1.5,                   1                   ),
    ANSWER_LOCAL(0,     NAN,                   NAN                 ),
    ANSWER_LOCAL(1,     3,                     NAN                 ),
    ANSWER_LOCAL(2,     23.9564392373896,      1.043560762610399   ),
    ANSWER_LOCAL(2,     0,                     -64                 ),
    ANSWER_LOCAL(2,     -0.27714467697981027,  -4.762855323020189  ),
    ANSWER_LOCAL(2,     9.328950638,           -9.328950638        ),
    ANSWER_LOCAL(0,     NAN,                   NAN                 ),
    ANSWER_LOCAL(1,     0.0659,                NAN                 )
};

#undef ANSWER_LOCAL

ExitCode RunUnitTests()
{
    ColorPrintf(GREEN, "Starting testing\n");
    ColorPrintf(GREEN, "--------------------------------------\n");

    size_t failed = 0;
    size_t num_of_tests = (sizeof(test_inputs)/sizeof(test_inputs[0]));
    for (size_t i = 0; i < num_of_tests; i++)
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

    if (IsZero(num_of_tests))
    {
        ColorPrintf(RED, "No tests were run\n");
    }
    else
    {
        double percent = IsZero(failed) ? 100 : (100*(num_of_tests-failed))/num_of_tests;
        ColorPrintf(YELLOW, "Percentage of passed: %lg%%\n", percent);
    }

    return ExitCodeEND_TEST;
}

ExitCode FileInputTestAnswers(FILE *fin_answers_p, EquationRoots *answers_ptr)
{
    DEBUGMyAssert(fin_answers_p != nullptr);
    DEBUGMyAssert(answers_ptr != nullptr);

    char line[MAXLEN] = "";
    char ch = '\0';

    FileReadLine(fin_answers_p, line);
    int res = sscanf(line, "%d %lg %lg %c", &answers_ptr->num_of_roots,
                                            &answers_ptr->x1, &answers_ptr->x2, &ch);
    if (res != answers_ptr->num_of_roots+1)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode FileInputNumOfTests(FILE *fin_coeffs_p, size_t *num_of_tests_p)
{
    DEBUGMyAssert(fin_coeffs_p != nullptr);
    DEBUGMyAssert(num_of_tests_p != nullptr);

    char line[MAXLEN] = "";
    char ch = '\0';

    FileReadLine(fin_coeffs_p, line);
    int res = sscanf(line, "%zu %c", num_of_tests_p, &ch);
    if (res != 1)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode FileRunUnitTests()
{
    FILE *fin_coeffs_p  = fopen("UnitTestsInput.txt",   "r");
    FILE *fin_answers_p = fopen("UnitTestsAnswers.txt", "r");
    if (fin_coeffs_p == nullptr || fin_answers_p == nullptr)
    {
        return ExitCodeFILE_ERROR;
    }

    size_t num_of_tests = 0;
    ExitCode status = FileInputNumOfTests(fin_coeffs_p, &num_of_tests);
    if (IsError(status))
    {
        return status;
    }

    ColorPrintf(GREEN, "Starting testing\n");
    ColorPrintf(GREEN, "--------------------------------------\n");

    size_t failed = 0;
    for (size_t i = 0; i < num_of_tests; i++)
    {
        struct EquationCoeffs coeffs = {NAN, NAN, NAN};
        struct EquationRoots roots   = {NumOfRootsNAN, NAN, NAN};
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

    if (IsZero(num_of_tests))
    {
        ColorPrintf(RED, "No tests were run\n");
    }
    else
    {
        double percent = IsZero(failed) ? 100 : (100*(num_of_tests-failed))/num_of_tests;
        ColorPrintf(YELLOW, "Percentage of passed: %lg%%\n", percent);
    }

    fclose(fin_coeffs_p);
    fclose(fin_answers_p);
    return ExitCodeEND_TEST;
}

bool IsFloatsEqual(double a, double b)
{
    if (isnan(a) && isnan(b))
    {
        return true;
    }
    a = fabs(a), b = fabs(b);
    return ((1-FLT_EPS)*b <= a && a <= (1+FLT_EPS)*b);
}

bool IsRootsEqual(const EquationRoots *roots1_ptr, const EquationRoots *roots2_ptr)
{
    DEBUGMyAssert(roots1_ptr != nullptr);
    DEBUGMyAssert(roots2_ptr != nullptr);

    bool nRoots_equal = (roots1_ptr->num_of_roots == roots2_ptr->num_of_roots);
    bool x1_equal = IsFloatsEqual(roots1_ptr->x1, roots2_ptr->x1);
    bool x2_equal = IsFloatsEqual(roots1_ptr->x2, roots2_ptr->x2);

    return (nRoots_equal && x1_equal && x2_equal);
}
