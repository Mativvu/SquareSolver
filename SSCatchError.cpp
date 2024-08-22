#include <stdio.h>
#include "SSErrorCodes.h"

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
            printf("Wrong input, try again \n");
            break;
        }
        case ExitCodeCOEFF_ERROR:
        {
            printf("Coefficients are not valid, enter again \n");
            break;
        }
        case ExitCodeSOLVER_ERROR:
        {
            printf("Number of roots is not valid \n");
            break;
        }
        case ExitCodeOUTPUT_ERROR:
        {
            printf("Error, solution is NaN \n");
            break;
        }
        case ExitCodeEND_TEST:
        {
            printf("Testing finished \n");
            break;
        }
        case ExitCodeMAXLEN_REACHED:
        {
            printf("Error, input line too long \n");
        }
        default:
        {
            printf("How did you get here? Everything is OK \n");
        }
    }
}

