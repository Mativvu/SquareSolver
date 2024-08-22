#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"
#include "SSInput.h"

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
