#include <stdio.h>

enum ExitCode
{
    ExitCodeOK,
    ExitCodeINPUT_ERROR,
    ExitCodeCOEFF_ERROR,
    ExitCodeSOLVER_ERROR,
    ExitCodeOUTPUT_ERROR,
    ExitCodeASSERT_FAIL
};

enum NumOfRoots
{
    NumOfRootsZERO,
    NumOfRootsONE,
    NumOfRootsTWO,
    NumOfRootsINF_SOLS,
    NumOfRootsNAN,
};

const double EPS = 1e-9;

struct EquationCoeffs {
    double a, b, c;
};


struct EquationRoots {
    NumOfRoots num_of_roots;
    double x1, x2;
};

ExitCode InputCoeffs(EquationCoeffs *eq_ptr);
ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr);

ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr)
{
    if (fscanf(fin_p, "%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c) != 3)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode InputCoeffs(EquationCoeffs *eq_ptr)
{
    printf("Enter coefficients of equation ax^2+bx+c=0 in format \"a b c\"\n");
    if (scanf("%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c) != 3)
    {
        return ExitCodeINPUT_ERROR;
    }
    printf("Your input: %lg % lg %lg \n", eq_ptr->a, eq_ptr->b, eq_ptr->c);
    return ExitCodeOK;
}
