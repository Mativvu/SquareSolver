#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSOutput.h"

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
            ColorPrintf(RED, "Wrong input, try again \n");
            break;
        }
        case ExitCodeCOEFF_ERROR:
        {
            ColorPrintf(RED, "Coefficients are not valid, enter again \n");
            break;
        }
        case ExitCodeSOLVER_ERROR:
        {
            ColorPrintf(RED, "Number of roots is not valid \n");
            break;
        }
        case ExitCodeOUTPUT_ERROR:
        {
            ColorPrintf(RED, "Error, solution is NaN \n");
            break;
        }
        case ExitCodeEND_TEST:
        {
            ColorPrintf(RED, "Testing finished \n");
            break;
        }
        case ExitCodeMAXLEN_REACHED:
        {
            ColorPrintf(RED, "Error, input line too long \n");
        }
        default:
        {
            ColorPrintf(RED, "How did you get here? Everything is OK \n");
        }
    }
}

