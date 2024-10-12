#include "ErrorCodes.h"
#include "Output.h"

#define printIfError(status, code, text) \
    if (status == code) printf(_RED text _RESET, code);

bool IsError(ExitCode status)
{
    return (status != ExitCodeOK);
}

void DescribeError(ExitCode status)
{
    printIfError(status, ExitCodeINPUT_ERROR,       "Err %d: "
                                                    "Wrong input, try again. \n");
    printIfError(status, ExitCodeCOEFF_ERROR,       "Err %d: "
                                                    "Coefficients are not valid, enter again. \n");
    printIfError(status, ExitCodeSOLVER_ERROR,      "Err %d: "
                                                    "Wrong input, try again. \n");
    printIfError(status, ExitCodeOUTPUT_ERROR,      "Err %d: "
                                                    "Number of roots is not valid. \n");
    printIfError(status, ExitCodeEND_TEST,          "Err %d: "
                                                    "Testing finished. \n");
    printIfError(status, ExitCodeMAXLEN_REACHED,    "Err %d: "
                                                    "Error, input line too long. \n");
    printIfError(status, ExitCodeUNKNOWN_ARG,       "Err %d: "
                                                    "Error, found unknown command. \n");
    printIfError(status, ExitCodeCOMMAND_ERROR,     "Err %d: "
                                                    "Error, cannot use --file and --input or --output together. \n");
    printIfError(status, ExitCodeFILE_ERROR,        "Err %d: "
                                                    "Error, cannot find/open file. \n");
    printIfError(status, ExitCodeDUPLICATION_ERROR, "Err %d: "
                                                    "Error, command duplication is forbidden. \n");
    printIfError(status, ExitCodeHELP_FLAG,         "Err %d: "
                                                    "Flag \"--help\" was inputted. \n");
    printIfError(status, ExitCodeOK,                "Err %d: "
                                                    "Function DescribeError called with OK status. \n");
    ColorPrintf(RED, "Error, unknown status. \n");
}

