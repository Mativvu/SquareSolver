#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"
#include "SSInput.h"

const int MAXLEN = 100;

ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr)
{
    char line[MAXLEN];
    int num_of_inputted = 0;

    FileReadLine(fin_p, line);
    num_of_inputted = sscanf(line, "%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c);
    if (num_of_inputted != 3)
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
ExitCode FileReadLine(FILE *fin_p, char *str)
{
    int len = 0;

    for(int ch = getc(fin_p);
        ch != '\n' && ch != EOF;
        ch = getc(fin_p))
    {
        if(len < MAXLEN)
        {
            str[len++] = ch;
        }
        else
        {
            return ExitCodeMAXLEN_REACHED;
        }
    }
    str[len] = '\0';
    return ExitCodeOK;
}
