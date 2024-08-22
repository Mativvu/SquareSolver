#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSOutput.h"

extern const char* ASNI_COLOR_RED;
extern const char* ASNI_COLOR_RESET;

bool IsError(ExitCode status)
{
    return (status != ExitCodeOK);
}

void DescribeError(ExitCode status)
{
    switch (status)
    {
        case ExitCodeINPUT_ERROR:
        {
            COLOR_RED_printf("Wrong input, try again \n");
            break;
        }
        case ExitCodeCOEFF_ERROR:
        {
            COLOR_RED_printf("Coefficients are not valid, enter again \n");
            break;
        }
        case ExitCodeSOLVER_ERROR:
        {
            COLOR_RED_printf("Number of roots is not valid \n");
            break;
        }
        case ExitCodeOUTPUT_ERROR:
        {
            COLOR_RED_printf("Error, solution is NaN \n");
            break;
        }
        case ExitCodeEND_TEST:
        {
            COLOR_RED_printf("Testing finished \n");
            break;
        }
        case ExitCodeMAXLEN_REACHED:
        {
            COLOR_RED_printf("Error, input line too long \n");
        }
        default:
        {
            COLOR_RED_printf("How did you get here? Everything is OK \n");
        }
    }
}

