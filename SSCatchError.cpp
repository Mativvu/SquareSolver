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
            ColorPrintf(RED, "Err %d: "
                             "Wrong input, try again \n",
                              ExitCodeINPUT_ERROR);
            break;
        }
        case ExitCodeCOEFF_ERROR:
        {
            ColorPrintf(RED, "Err %d: "
                             "Coefficients are not valid, enter again \n",
                             ExitCodeCOEFF_ERROR);
            break;
        }
        case ExitCodeSOLVER_ERROR:
        {
            ColorPrintf(RED, "Err %d: "
                             "Number of roots is not valid \n",
                             ExitCodeSOLVER_ERROR);
            break;
        }
        case ExitCodeOUTPUT_ERROR:
        {
            ColorPrintf(RED, "Err %d: "
                             "Error, solution is NaN \n",
                             ExitCodeOUTPUT_ERROR);
            break;
        }
        case ExitCodeEND_TEST:
        {
            ColorPrintf(RED, "Err %d: "
                             "Testing finished \n",
                             ExitCodeEND_TEST);
            break;
        }
        case ExitCodeMAXLEN_REACHED:
        {
            ColorPrintf(RED, "Err %d: "
                             "Error, input line too long \n",
                             ExitCodeMAXLEN_REACHED);
            break;
        }
        case ExitCodeUNKNOWN_ARG:
        {
            ColorPrintf(RED, "Err %d: "
                             "Error, found unknown command \n",
                             ExitCodeUNKNOWN_ARG);
            break;
        }
        case ExitCodeCOMMAND_ERROR:
        {
            ColorPrintf(RED, "Err %d: "
                             "Error, cannot use --file and --input or --output together \n",
                             ExitCodeCOMMAND_ERROR);
            break;
        }
        case ExitCodeFILE_ERROR:
        {
            ColorPrintf(RED, "Err %d: "
                             "Error, cannot find/open file \n",
                             ExitCodeFILE_ERROR);
            break;
        }
        case ExitCodeDUPLICATION_ERROR:
        {
            ColorPrintf(RED, "Err %d: "
                             "Error, command duplication is forbidden\n",
                             ExitCodeDUPLICATION_ERROR);
        }
        case ExitCodeOK:
        {
            ColorPrintf(RED, "Err %d: "
                             "Function DescribeError called with OK status \n",
                             ExitCodeOK);
            break;
        }
        default:
        {
            ColorPrintf(RED, "Error, unknown status \n");
            break;
        }
    }
}

