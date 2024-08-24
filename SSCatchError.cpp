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
            break;
        }
        case ExitCodeUNKNOWN_ARG:
        {
            ColorPrintf(RED, "Error, found unknown command \n");
            break;
        }
        case ExitCodeCOMMAND_ERROR:
        {
            ColorPrintf(RED, "Error, cannot use --file and --input or --output together \n");
            break;
        }
        case ExitCodeFILE_ERROR:
        {
            ColorPrintf(RED, "Error, cannot find/open file \n");
            break;
        }
        case ExitCodeDUPLICATION_ERROR:
        {
            ColorPrintf(RED, "Error, command duplication is forbidden\n");
        }
        case ExitCodeOK:
        {
            ColorPrintf(RED, "Function DescribeError called with OK status \n");
            break;
        }
        default:
        {
            ColorPrintf(RED, "Error, unknown status \n");
            break;
        }
    }
}

