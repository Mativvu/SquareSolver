#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG

#ifdef DEBUG
// $ __FUNCTION__
#define DEBUGPrintStr(string) printf(string)
#define DEBUGPrintEquation(expr) printf("Identified equation: " #expr "\n")
#define DEBUGMyAssert(expr)                            \
if(!(expr))                                            \
{                                                      \
    printf("Assert fail line %d, expr: " #expr " file %s",   \
    __LINE__, __FILE__);                               \
    exit(1);                                           \
}
#else
#define DEBUGPrintStr(string) ;
#define DEBUGPrintEquation(expr) ;
#define DEBUGMyAssert(expr) ;
#endif

enum ExitCode
{
    ExitCodeOK,
    ExitCodeINPUT_ERROR,
    ExitCodeCOEFF_ERROR,
    ExitCodeSOLVER_ERROR,
    ExitCodeOUTPUT_ERROR,
    ExitCodeASSERT_FAIL
};

enum NumOfRoots
{
    NumOfRootsZERO,
    NumOfRootsONE,
    NumOfRootsTWO,
    NumOfRootsINF_SOLS,
    NumOfRootsNAN,
};

const double EPS = 1e-9;

struct EquationCoeffs {
    double a, b, c;
};


struct EquationRoots {
    NumOfRoots num_of_roots;
    double x1, x2;
};

ExitCode SolveQuadEquation(EquationCoeffs *eq_ptr, EquationRoots *roots_ptr);

ExitCode InputCoeffs(EquationCoeffs *eq_ptr);
ExitCode PrintSolutions(EquationRoots *roots_ptr);
void DescribeError(ExitCode status);

ExitCode FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr);
ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr);
void FileDescribeError(FILE *fout_p, ExitCode status);

bool IsValid(double coeff);
bool IsZero(double coeff);
bool IsError(ExitCode status);

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
