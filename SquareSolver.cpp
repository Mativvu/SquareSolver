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
#include "SSFlagsAndFiles.h"

// TODO:
// Doxygen (docs)
// README.md markdown browser
// Google Tests. python ... autotools GNU (GNU Compiler Collection)
// README.md
// --- - - - --Make Makefile!
// {} {0} {'\0'} "" - initialization

int main(const int argc, const char *argv[])
{
    int mode_field = 0;
    DEBUGMyAssert(mode_field != 0);

    const char *fin_name = nullptr;
    const char *fout_name = nullptr;
    ExitCode status = ProcessMainArgs(argc, argv, &mode_field, &fin_name, &fout_name);
    if (IsError(status))
    {
        DescribeError(status);
        return status;
    }

    IsModeSet(mode_field, ModeRT) ? PrintRT() : ColorPrintf(RED, "No RT((((\n");

    IsModeSet(mode_field, ModeHelp) ? PrintCommands()
                                    : ColorPrintf(MAGENTA, "Use --help to see commands\n");

    FILE *fin_p = nullptr;
    FILE *fout_p = nullptr;
    status = FileManager(mode_field, &fin_p, &fout_p, fin_name, fout_name);
    if (IsError(status))
    {
        DescribeError(status);
        return status;
    }
    DEBUGPrintStr("Initialization completed, files opened successfully");

    if (IsModeSet(mode_field, ModeTest))
    {
        status = IsModeSet(mode_field, ModeFile) ? FileRunUnitTests()
                                                 : RunUnitTests();
        if (IsError(status))
        {
            DescribeError(status);
        }
        return 0;
    }

    struct EquationCoeffs equation = {NAN, NAN, NAN};
    struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};

    status = (IsModeSet(mode_field, (ModeFile | ModeInput))) ? FileInputCoeffs(fin_p, &equation)
                                                             : InputCoeffs(&equation);
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

    status = ((IsModeSet(mode_field, (ModeFile | ModeOutput))) ? FilePrintSolutions(fout_p, &roots)
                                                               : PrintSolutions(&roots));
    if (IsError(status))
    {
        DescribeError(status);
        return status;
    }
    DEBUGPrintStr("Output finished successfully");

    fclose(fin_p);
    fclose(fout_p);
}
