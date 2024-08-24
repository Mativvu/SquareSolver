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


// --- - - - --Make Makefile!

// bool OptionsEnabled[Size];
// OptionsEnabled[ModeTest] = true;
// rwx

enum Mode {
    ModeTest   = 1U << 0,
    ModeFile   = 1U << 1,
    ModeDebug  = 1U << 2,
    ModeHelp   = 1U << 3,
    ModeInput  = 1U << 4,
    ModeOutput = 1U << 5
};

struct Command {
    Mode mode;
    const char* name;
    const char* short_name;
    const char* describtion;
};

static Command Commands[] = {
    {ModeTest,   "--test",  "-t", "to start unit testing, add --file to get tests "
                                  "from \"UnitTestssAnswers\" and \"UnitTestsInput\"\n"},
    {ModeDebug,  "--debug", "-d", "to turn on debug mode\n"},
    {ModeFile,   "--file",  "-f", "to use \"input.txt\" and \"output.txt\" files\n"},
    {ModeHelp,   "--help",  "-h", "you already know, don`t you?)\n"},
    {ModeInput,  "--in",    "-i", "\"filename\" to input from filename\n"},
    {ModeOutput, "--out",   "-o", "\"filename\" to output to filename\n"}
};

ExitCode ProcessMainArgs(int argc, char *argv[], int *mode_field, const char **fin_name, const char **fout_name);
ExitCode FileManager(int mode, FILE **fin_p, FILE **fout_p, const char *fin_name, const char *fout_name);
bool IsModeSet(int mode_field, int mode);
bool IsValidCommand(char* str, Command command);
void PrintCommands();

int main(int argc, char *argv[])
{
    int mode_field = 0;
    const char *fin_name = nullptr;
    const char *fout_name = nullptr;
    ExitCode status = ProcessMainArgs(argc, argv, &mode_field, &fin_name, &fout_name);
    if (IsError(status))
    {
        DescribeError(status);
        return status;
    }

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

ExitCode ProcessMainArgs(int argc, char *argv[], int *mode_field, const char **fin_name, const char **fout_name)
{
    for (int i = 1; i < argc; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (sizeof(Commands)/sizeof(Commands[0])); j++)
        {
            if (IsValidCommand(argv[i], Commands[j]))
            {
                if (IsModeSet(*mode_field, Commands[j].mode))
                {
                    return ExitCodeDUPLICATION_ERROR;
                }
                *mode_field |= Commands[j].mode;

                if (IsValidCommand(argv[i], Commands[4]) && ++i < argc)      //???
                {
                    *fin_name = argv[i];
                }
                else if (IsValidCommand(argv[i], Commands[5]) && ++i < argc) //????
                {
                    *fout_name = argv[i];
                }
                found = true;
                break;
            }
        }
        if(!found)
        {
            ColorPrintf(MAGENTA, "%s ", argv[i]);
            return ExitCodeUNKNOWN_ARG;
        }
    }
    return ExitCodeOK;
}

ExitCode FileManager(int mode, FILE **fin_p, FILE **fout_p, const char *fin_name, const char *fout_name)
{
    DEBUGMyAssert(fin_p != nullptr);
    DEBUGMyAssert(fout_p != nullptr);

    if (IsModeSet(mode, ModeFile) && IsModeSet(mode, (ModeInput | ModeOutput)))
    {
        return ExitCodeCOMMAND_ERROR;
    }
    if (IsModeSet(mode, ModeFile))
    {
        *fin_p = fopen("input.txt", "r");
        *fout_p = fopen("output.txt", "w");
        if (*fin_p == nullptr || *fout_p == nullptr)
        {
            return ExitCodeFILE_ERROR;
        }
    }
    if (fin_name != nullptr)
    {
        *fin_p = fopen(fin_name, "r");
        if (*fin_p == nullptr)
        {
            return ExitCodeFILE_ERROR;
        }
    }
    if (fout_name != nullptr)
    {
        *fout_p = fopen(fout_name, "w");
        if (*fout_p == nullptr)
        {
            return ExitCodeFILE_ERROR;
        }
    }
    return ExitCodeOK;
}

bool IsModeSet(int mode_field, int mode)
{
    return (mode_field & mode);
}

bool IsValidCommand(char* str, Command command)
{
    return (strcmp(str, command.name) == 0 ||
            strcmp(str, command.short_name) == 0);
}

void PrintCommands()
{
    printf("\n");
    for (size_t i = 0; i < (sizeof(Commands)/sizeof(Commands[0])); i++)
    {
        ColorPrintf(CYAN, "%s or %s ", Commands[i].name, Commands[i].short_name);
        ColorPrintf(MAGENTA, "%s\n", Commands[i].describtion);
    }
}



