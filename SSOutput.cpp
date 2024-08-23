#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <string>
#include "SSErrorCodes.h"
#include "SSStructures.h"
#include "SSOutput.h"
#include "SSSolve.h"
#include "SSDebug.h"

const char* RED    = "\x1b[31m";
const char* GREEN  = "\x1b[32m";
const char* YELLOW = "\x1b[33m";
const char* BLUE   = "\x1b[34m";
const char* MAGENTA= "\x1b[35m";
const char* CYAN   = "\x1b[36m";
const char* RESET  = "\x1b[0m";

void ColorPrintf(const char *color, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("%s", color);
    vprintf(format, args);
    printf("%s", RESET);
    va_end(args);
}

ExitCode FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr)
{
    DEBUGMyAssert(roots_ptr != nullptr);
    switch(roots_ptr->num_of_roots)
    {
        case 0:
        {
            fprintf(fout_p, "No solutions \n");
            break;
        }
        case 1:
        {
            if (!IsValid(roots_ptr->x1))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            fprintf(fout_p, "One solution: %lg \n", roots_ptr->x1);
            break;
        }
        case 2:
        {
            if (!IsValid(roots_ptr->x1) || !IsValid(roots_ptr->x2))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            fprintf(fout_p, "First solution: %lg, second solution: %lg \n", roots_ptr->x1, roots_ptr->x2);
            break;
        }
        case INF_SOLS:
        {
            fprintf(fout_p, "Any number \n");
            break;
        }
        case NAN_ROOTS:
        {
            return ExitCodeSOLVER_ERROR;
        }
    }
    return ExitCodeOK;
}

ExitCode PrintSolutions(EquationRoots *roots_ptr)
{
    DEBUGMyAssert(roots_ptr != nullptr);
    switch(roots_ptr->num_of_roots)
    {
        case 0:
        {
            printf("No solutions \n");
            break;
        }
        case 1:
        {
            if (!IsValid(roots_ptr->x1))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            printf("One solution: %lg \n", roots_ptr->x1);
            break;
        }
        case 2:
        {
            if (!IsValid(roots_ptr->x1) || !IsValid(roots_ptr->x2))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            printf("First solution: %lg, second solution: %lg \n", roots_ptr->x1, roots_ptr->x2);
            break;
        }
        case INF_SOLS:
        {
            printf("Any number \n");
            break;
        }
        case NAN_ROOTS:
        {
            return ExitCodeSOLVER_ERROR;
        }
    }
    return ExitCodeOK;
}
