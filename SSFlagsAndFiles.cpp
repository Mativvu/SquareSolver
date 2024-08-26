#include <string>

#include "SSFlagsAndFiles.h"
#include "SSOutput.h"
#include "SSDebug.h"

static Command Commands[] = {
    {ModeTest,   "--test",  "-t", "to start unit testing, add --file to get tests "
                                  "from \"UnitTestssAnswers\" and \"UnitTestsInput\"\n"},
    {ModeDebug,  "--debug", "-d", "to turn on debug mode\n"},
    {ModeFile,   "--file",  "-f", "to use \"input.txt\" and \"output.txt\" files\n"},
    {ModeHelp,   "--help",  "-h", "you already know, don`t you?)\n"},
    {ModeInput,  "--in",    "-i", "\"filename\" to input from filename\n"},
    {ModeOutput, "--out",   "-o", "\"filename\" to output to filename\n"},
    {ModeRT,     "--RT",    "-r", "to draw RT from RT.txt file! RTRTRTRTRTRTRTRTRT\n"}
};

ExitCode ProcessMainArgs(const int argc, const char *argv[], int *mode_field, const char **fin_name, const char **fout_name)
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

ExitCode FileManager(int mode_field, FILE **fin_p, FILE **fout_p, const char *fin_name, const char *fout_name)
{
    DEBUGMyAssert(fin_p != nullptr);
    DEBUGMyAssert(fout_p != nullptr);

    if (IsModeSet(mode_field, ModeFile) && IsModeSet(mode_field, (ModeInput | ModeOutput)))
    {
        return ExitCodeCOMMAND_ERROR;
    }
    if (IsModeSet(mode_field, ModeFile))
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

bool IsValidCommand(const char* str, Command command)
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
    while (getline(&line, &len, fin_p) != -1)
    {
        ColorPrintf(RED, "%s", line);
        system ("say -v Yuri \"ЭРРРРР ТЭЭЭЭЭ\"");
    }
    printf("\n");
    fclose(fin_p);
}
