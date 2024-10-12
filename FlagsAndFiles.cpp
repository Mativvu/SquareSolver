#include <string>
#include <stdio.h>

#include "FlagsAndFiles.h"
#include "Output.h"
#include "Debug.h"

static Command Commands[] = {
    {ModeTest,   "--test",  "-t", "to start unit testing, add --file to get tests "
                                  "from \"UnitTestssAnswers\" and \"UnitTestsInput\". "
                                  "See documentation for more details. \n"},
    {ModeDebug,  "--debug", "-d", "to turn on debug mode\n"},
    {ModeFile,   "--file",  "-f", "to use \"input.txt\" and \"output.txt\" files\n"},
    {ModeHelp,   "--help",  "-h", "you already know, don`t you?)\n"},
    {ModeInput,  "--in",    "-i", "type \"filename\" after it to input from filename\n"},
    {ModeOutput, "--out",   "-o", "type \"filename\" after it to output to filename\n"},
    {ModeRT,     "--RT",    "-r", "to draw RT from RT.txt file! RTRTRTRTRTRTRTRTRT\n"}
};

ExitCode ProcessMainArgs(const int argc, const char *argv[], int *mode_field,
                         const char **fin_name, const char **fout_name)
{
    DEBUGMyAssert(mode_field != nullptr);
    DEBUGMyAssert(fin_name != nullptr);
    DEBUGMyAssert(fout_name != nullptr);

    for (int i = 1; i < argc; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (sizeof(Commands)/sizeof(Commands[0])); j++)
        {
            if (IsCommand(argv[i], &Commands[j]))
            {
                if (IsModeSet(*mode_field, Commands[j].mode))
                {
                    return ExitCodeDUPLICATION_ERROR;
                }
                *mode_field |= Commands[j].mode;

                // Simple solution to process commands "--in" and "--out".
                if (IsCommand(argv[i], &Commands[FLAG_IN_INDEX])
                    && i+1 < argc)
                {
                    *fin_name = argv[++i];
                }
                else if (IsCommand(argv[i], &Commands[FLAG_OUT_INDEX])
                         && i+1 < argc)
                {
                    *fout_name = argv[++i];
                }
                found = true;
                break;
            }
        }
        if (!found)
        {
            ColorPrintf(MAGENTA, "Found unknown argument: %s\n", argv[i]);
            return ExitCodeUNKNOWN_ARG;
        }
    }
    return ExitCodeOK;
}

ExitCode FileManager(int mode_field, FILE **fin_p, FILE **fout_p,
                     const char *fin_name, const char *fout_name)
{
    DEBUGMyAssert(fin_p != nullptr);
    DEBUGMyAssert(fout_p != nullptr);

    if (   IsAllModesSet(mode_field, (ModeFile | ModeOutput))
        || IsAllModesSet(mode_field, (ModeFile | ModeInput)))
    {
        return ExitCodeCOMMAND_ERROR;
    }
    if (IsModeSet(mode_field, ModeFile))
    {
        *fin_p  = fopen("input.txt",  "r");
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

bool IsAllModesSet(int mode_field, int modes)
{
    return ((mode_field & modes) == modes);
}

bool IsAnyModesSet(int mode_field, int modes)
{
    return (mode_field & modes);
}

bool IsModeSet(int mode_field, int mode)
{
    return (mode_field & mode);
}

bool IsCommand(const char* str, const Command* command)
{
    return (strcmp(str, command->name)       == 0 ||
            strcmp(str, command->short_name) == 0);
}

void PrintCommands()
{
    printf("\n");
    for (size_t i = 0; i < (sizeof(Commands)/sizeof(Commands[0])); i++)
    {
        ColorPrintf(CYAN, "%s ", Commands[i].name);
        ColorPrintf(MAGENTA, "or ");
        ColorPrintf(CYAN, "%s ", Commands[i].short_name);
        ColorPrintf(MAGENTA, "%s\n", Commands[i].describtion);
    }
}

void PrintRT()
{
    FILE *fin_p = fopen("RT.txt", "r");
    if(fin_p == nullptr)
    {
        ColorPrintf(RED, "Cannot open RT.txt file(((\n");
        return;
    }

    char* line = nullptr;
    size_t len = 0;
    while (getline(&line, &len, fin_p) != EOF)
    {
        ColorPrintf(RED, "%s", line);
        system ("say -v Yuri \"ЭРРРРР ТЭЭЭЭЭ\"");
    }
    printf("\n");
    fclose(fin_p);
}

ExitCode PerformPrintingCommands(int mode_field)
{
    if (IsModeSet(mode_field, ModeHelp))
    {
        PrintCommands();
        return ExitCodeHELP_FLAG;
    }
    else
    {
        ColorPrintf(MAGENTA, "Type --help to see commands\n");
    }

    IsModeSet(mode_field, ModeRT) ? PrintRT() : ColorPrintf(RED, "No RT((((\n");

    if (IsModeSet(mode_field, ModeDebug))
    {
        ColorPrintf(MAGENTA, "You cannot turn debug mode on with this command, because "
                             "its a #define, but you can uncomment \"#define DEBUG\" "
                             "in SSDebug.h file to turn it on.\n");
    }
    return ExitCodeOK;
}

