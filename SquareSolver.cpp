#include <math.h>
#include <stdio.h>

#include "Debug.h"
#include "Structures.h"
#include "Input.h"
#include "Solve.h"
#include "Output.h"
#include "UnitTest.h"
#include "FlagsAndFiles.h"

int main(const int argc, const char *argv[])
{
    int mode_field = 0;

    const char *fin_name = nullptr;
    const char *fout_name = nullptr;
    ExitCode status = ProcessMainArgs(argc, argv, &mode_field, &fin_name, &fout_name);
    checkStatus(status);

    status = PerformPrintingCommands(mode_field);
    checkStatus(status);

    FILE *fin_p = nullptr;
    FILE *fout_p = nullptr;
    status = FileManager(mode_field, &fin_p, &fout_p, fin_name, fout_name);
    checkStatus(status);
    DEBUGPrintStr("Initialization completed, files opened successfully");

    if (IsModeSet(mode_field, ModeTest))
    {
        status = IsModeSet(mode_field, ModeFile) ? FileRunUnitTests()
                                                 : RunUnitTests();
        checkStatus(status);
        return 0;
    }

    struct EquationCoeffs equation = {NAN, NAN, NAN};
    struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};

    status = (IsAnyModesSet(mode_field, (ModeFile | ModeInput)))
            ? FileInputCoeffs(fin_p, &equation)
            : InputCoeffs(&equation);
    checkStatus(status);
    DEBUGPrintStr("Input completed");

    status = SolveQuadEquation(&equation, &roots);
    checkStatus(status);
    DEBUGPrintStr("Solving function finished");

    status = ((IsAnyModesSet(mode_field, (ModeFile | ModeOutput)))
             ? FilePrintSolutions(fout_p, &roots)
             : PrintSolutions(&roots));
    checkStatus(status);
    DEBUGPrintStr("Output finished successfully");

    fclose(fin_p);
    fclose(fout_p);
}
