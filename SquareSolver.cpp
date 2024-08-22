#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <math.h>

#include "SSDebug.h"
#include "SSStructures.h"
#include "SSInput.h"
#include "SSSolve.h"
#include "SSOutput.h"
#include "SSUnitTest.h"

// *const
//FileDescribeError delete
// Doxygen (docs)
// README.md markdown browser
// 1 2 3 g
// f

int main()
{
    FILE *fin_p = stdin;
    FILE *fout_p = stdout;
    #ifdef FILEMODE
    fin_p = fopen("input", "r");
    fout_p = fopen("output", "w");
    #endif

    struct EquationCoeffs equation = {NAN, NAN, NAN};
    struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};
    ExitCode status = ExitCodeOK;

    #ifdef UNITEST
    status = RunUnitTests();
    if (IsError(status))
    {
        DescribeError(status);
    }
    return 0;
    #endif

    DEBUGPrintStr("Initialization completed, files opened successfully");
    status = FileInputCoeffs(fin_p, &equation);
    if (IsError(status))
    {
        DescribeError(status);
        return status;
    }
    DEBUGPrintStr("Input completed");
    status = SolveQuadEquation(&equation, &roots);
    if (IsError(status))
    {
        DescribeError(status);
        return status;
    }
    DEBUGPrintStr("Solving function finished");
    status = FilePrintSolutions(fout_p, &roots);
    if (IsError(status))
    {
        DescribeError(status);
        return status;
    }
    DEBUGPrintStr("Output finished successfully");
}



