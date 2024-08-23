#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <string>

#include "SSDebug.h"
#include "SSStructures.h"
#include "SSInput.h"
#include "SSSolve.h"
#include "SSOutput.h"
#include "SSUnitTest.h"

// Doxygen (docs)
// README.md markdown browser


// --interactive
// --file
// Сделай как-нибудь!

// Google Tests. python ... autotools GNU (GNU Compiler Collection)

// README.md

enum Mode
{
    ModeTest = 1,
    ModeFile = 2
};

void ProcessMainArgs(int argc, char *argv[], int *mode);

int main(int argc, char *argv[])
{
    ColorPrintf(MAGENTA, "You can start program with arguments: \n"
           "-file to turn on file input and output\n"
           "-test to start unit testing\n\n");

    int mode = 0;
    ProcessMainArgs(argc, argv, &mode);

    FILE *fin_p = stdin;
    FILE *fout_p = stdout;
    if(mode & ModeFile)
    {
        fin_p = fopen("input", "r");
        fout_p = fopen("output", "w");
    }

    struct EquationCoeffs equation = {NAN, NAN, NAN};
    struct EquationRoots roots = {NAN_ROOTS, NAN, NAN};
    ExitCode status = ExitCodeOK;

    if(mode & ModeTest)
    {
        status = RunUnitTests();
        if (IsError(status))
        {
            DescribeError(status);
        }
        return 0;
    }

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

void ProcessMainArgs(int argc, char *argv[], int *mode)
{
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-file") == 0)
        {
            *mode |= ModeFile;
            ColorPrintf(MAGENTA, "Found -test\n");
        }
        else if(strcmp(argv[i], "-test") == 0)
        {
            *mode |= ModeTest;
            ColorPrintf(MAGENTA, "Found -test\n");
        }
        else if(argv[i][0] == '-')
        {
            ColorPrintf(MAGENTA, "Unknown command %s\n", argv[i]);
        }
    }
    printf("\n");
}



