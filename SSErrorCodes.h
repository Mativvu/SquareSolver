#ifndef SSERRORCODES_H
#define SSERRORCODES_H
#include <stdio.h>

enum ExitCode
{
    ExitCodeOK,
    ExitCodeINPUT_ERROR,
    ExitCodeCOEFF_ERROR,
    ExitCodeSOLVER_ERROR,
    ExitCodeOUTPUT_ERROR,
    ExitCodeEND_TEST,
    ExitCodeMAXLEN_REACHED
};

bool IsError(ExitCode status);
void DescribeError(ExitCode status);

#endif
