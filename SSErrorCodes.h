#include <stdio.h>
#ifndef SSERRORCODES_H
#define SSERRORCODES_H

enum ExitCode
{
    ExitCodeOK,
    ExitCodeINPUT_ERROR,
    ExitCodeCOEFF_ERROR,
    ExitCodeSOLVER_ERROR,
    ExitCodeOUTPUT_ERROR,
    ExitCodeASSERT_FAIL
};

void FileDescribeError(FILE *fout_p, ExitCode status); //???
void DescribeError(ExitCode status);
bool IsError(ExitCode status);

#endif
