#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "SSErrorCodes.h"

#include "SSInput.cpp"
#include "SSInput.h"

#include "SSoutput.cpp"
#include "SSOutput.h"

#include "SSSolve.cpp"
#include "SSSolve.h"

#include "SSStructures.h"
#include "SSDebug.h"
#include "SSUnitTest.h"

int main()
{
    FILE *fin_p = fopen("input", "r");
    FILE *fout_p = fopen("output", "w");

    struct EquationCoeffs equation = {NAN, NAN, NAN};
    struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};
    ExitCode status = ExitCodeOK;

    DEBUGPrintStr("Initialization completed, files opened successfully \n");
    status = FileInputCoeffs(fin_p, &equation);
    if (IsError(status))
    {
        FileDescribeError(fout_p, status);
        return status;
    }
    DEBUGPrintStr("Input completed \n");
    status = SolveQuadEquation(&equation, &roots);
    if (IsError(status))
    {
        FileDescribeError(fout_p, status);
        return status;
    }
    DEBUGPrintStr("Solving function finished \n");
    status = FilePrintSolutions(fout_p, &roots);
    if (IsError(status))
    {
        FileDescribeError(fout_p, status);
        return status;
    }
    DEBUGPrintStr("Output finished successfully \n");
}
