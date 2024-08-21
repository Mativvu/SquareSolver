#include <stdio.h>

enum ExitCode
{
    ExitCodeOK,
    ExitCodeINPUT_ERROR,
    ExitCodeCOEFF_ERROR,
    ExitCodeSOLVER_ERROR,
    ExitCodeOUTPUT_ERROR,
    ExitCodeASSERT_FAIL
};

void FileDescribeError(FILE *fout_p, ExitCode status);
void DescribeError(ExitCode status);
bool IsError(ExitCode status);

void FileDescribeError(FILE *fout_p, ExitCode status)
{
    switch (status)
    {
        case ExitCodeINPUT_ERROR:
        {
            fprintf(fout_p, "Wrong input, try again \n");
            break;
        }
        case ExitCodeCOEFF_ERROR:
        {
            fprintf(fout_p, "Coefficients are not valid, enter again \n");
            break;
        }
        case ExitCodeSOLVER_ERROR:
        {
            fprintf(fout_p, "Number of roots is not valid \n");
            break;
        }
        case ExitCodeOUTPUT_ERROR:
        {
            fprintf(fout_p, "Error, solution is NaN \n");
            break;
        }
        case ExitCodeASSERT_FAIL:
        {
            fprintf(fout_p, "Program finished with error \n");
        }
        default:
        {
            fprintf(fout_p, "How did you get here? Everything is OK");
        }
    }
}

void DescribeError(ExitCode status)
{
    switch (status)
    {
        case ExitCodeINPUT_ERROR:
        {
            printf("Wrong input, try again \n");
            break;
        }
        case ExitCodeCOEFF_ERROR:
        {
            printf("Coefficients are not valid, enter again \n");
            break;
        }
        case ExitCodeSOLVER_ERROR:
        {
            printf("Number of roots is not valid \n");
            break;
        }
        case ExitCodeOUTPUT_ERROR:
        {
            printf("Error, solution is NaN \n");
            break;
        }
        case ExitCodeASSERT_FAIL:
        {
            printf("Program finished with error \n");
        }
        default:
        {
            printf("How did you get here? Everything is OK \n");
        }
    }
}

bool IsError(ExitCode status)
{
    return (status != ExitCodeOK);
}
