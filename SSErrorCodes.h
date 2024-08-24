#ifndef SSERRORCODES_H
#define SSERRORCODES_H
#include <stdio.h>

enum ExitCode {
    ExitCodeOK,
    ExitCodeINPUT_ERROR,
    ExitCodeCOEFF_ERROR,
    ExitCodeSOLVER_ERROR,
    ExitCodeOUTPUT_ERROR,
    ExitCodeEND_TEST,
    ExitCodeMAXLEN_REACHED,
    ExitCodeUNKNOWN_ARG,
    ExitCodeCOMMAND_ERROR,
    ExitCodeFILE_ERROR,
    ExitCodeDUPLICATION_ERROR
};

bool IsError(ExitCode status);
void DescribeError(ExitCode status);

#endif
