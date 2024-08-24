#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"
#include "SSInput.h"
#include "SSDebug.h"

ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr)
{
    DEBUGMyAssert(fin_p != nullptr);
    DEBUGMyAssert(eq_ptr != nullptr);

    char line[MAXLEN];

    FileReadLine(fin_p, line);
    int res = sscanf(line, "%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c);
    if (res != 3)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode InputCoeffs(EquationCoeffs *eq_ptr)
{
    DEBUGMyAssert(eq_ptr != nullptr);

    printf("Enter coefficients of equation ax^2+bx+c=0 in format \"a b c\"\n");

    char line[MAXLEN];

    FileReadLine(stdin, line);
    int res = sscanf(line, "%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c);
    if (res != 3)
    {
        return ExitCodeINPUT_ERROR;
    }
    printf("Your input: %lg %lg %lg \n", eq_ptr->a, eq_ptr->b, eq_ptr->c);
    return ExitCodeOK;
}

ExitCode FileReadLine(FILE *fin_p, char *str)
{
    DEBUGMyAssert(fin_p != nullptr);

    int len = 0;
    int ch = getc(fin_p);
    while(ch != '\n' && ch != EOF)
    {
        if(len < MAXLEN)
        {
            str[len++] = (char)ch;
        }
        else
        {
            return ExitCodeMAXLEN_REACHED;
        }
        ch = getc(fin_p);
    }
    str[len] = '\0';
    return ExitCodeOK;
}
