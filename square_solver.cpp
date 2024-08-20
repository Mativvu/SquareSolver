#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG

#ifdef DEBUG
#define DebugPrint(expr) printf("Identified equation: " #expr "\n")
#endif

enum ExitCode
{
    ExitCodeOK,
    ExitCodeINPUT_ERROR,
    ExitCodeCOEFF_ERROR,
    ExitCodeSOLVER_ERROR,
    ExitCodeOUTPUT_ERROR,
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

ExitCode SolveQuadEquation(struct EquationCoeffs *eq_ptr, struct EquationRoots *roots_ptr);

ExitCode FileInputCoeffs(FILE *fin_p, FILE *fout_p, struct EquationCoeffs *eq_ptr);
ExitCode InputCoeffs(struct EquationCoeffs *eq_ptr);

ExitCode FilePrintSolutions(FILE *fout_p, struct EquationRoots *roots_ptr);
ExitCode PrintSolutions(struct EquationRoots *roots_ptr);

void FileDescribeError(FILE *fout_p, ExitCode status);
void DescribeError(ExitCode status);

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

    #ifdef DEBUG
    printf("Initialization completed, files opened successfully \n");
    #endif
    status = FileInputCoeffs(fin_p, fout_p, &equation);
    if (IsError(status))
    {
        FileDescribeError(fout_p, status);
        return status;
    }
    #ifdef DEBUG
    printf("Input completed \n");
    #endif
    status = SolveQuadEquation(&equation, &roots);
    if (IsError(status))
    {
        FileDescribeError(fout_p, status);
        return status;
    }
    #ifdef DEBUG
    printf("Solving function finished \n");
    #endif
    status = FilePrintSolutions(fout_p, &roots);
    if (IsError(status))
    {
        FileDescribeError(fout_p, status);
        return status;
    }
    #ifdef DEBUG
    printf("Output finished successfully \n");
    #endif
}

ExitCode SolveQuadEquation(struct EquationCoeffs *eq_ptr, struct EquationRoots *roots_ptr)
{
    double a = eq_ptr->a;
    double b = eq_ptr->b;
    double c = eq_ptr->c;

    if(!(IsValid(a) && IsValid(b) && IsValid(c)))
    {
        return ExitCodeCOEFF_ERROR;
    }

    if (IsZero(a))
    {
        if (IsZero(b))
        {
            #ifdef DEBUG
            DebugPrint("c = 0");
            #endif
            roots_ptr->num_of_roots = (IsZero(c)) ? NumOfRootsINF_SOLS : NumOfRootsZERO;
        }
        else
        {
            #ifdef DEBUG
            DebugPrint("bx+c = 0");
            #endif
            roots_ptr->x1 = (IsZero(c)) ? 0 : -(c/b);
            roots_ptr->num_of_roots = NumOfRootsONE;
        }
    }
    else
    {
        if (IsZero(b) && c < -EPS)
        {
            #ifdef DEBUG
            DebugPrint("ax^2+c = 0");
            #endif
            roots_ptr->x1 = sqrt(c/a);
            roots_ptr->x2 = -sqrt(c/a);
            roots_ptr->num_of_roots = NumOfRootsTWO;
        }
        else
        {
            double D = b*b - 4*a*c;
            double sqrt_D = sqrt(D);
            if (IsZero(D))
            {
                #ifdef DEBUG
                DebugPrint("ax^2+bx+c = 0, D=0");
                #endif
                roots_ptr->x1 = -b/(2*a);
                roots_ptr->num_of_roots = NumOfRootsONE;
            }
            else if (D > EPS)
            {
                #ifdef DEBUG
                DebugPrint("ax^2+bx+c = 0, D>0");
                #endif
                roots_ptr->x1 = (-b + sqrt_D)/(2*a);
                roots_ptr->x2 = (-b - sqrt_D)/(2*a);
                roots_ptr->num_of_roots = NumOfRootsTWO;
            }
            else
            {
                #ifdef DEBUG
                DebugPrint("ax^2+bx+c = 0, D<0");
                #endif
                roots_ptr->num_of_roots = NumOfRootsZERO;
            }
        }
    }
    return ExitCodeOK;
}

bool IsZero(double coeff)
{
    return (fabs(coeff) < EPS);
}

bool IsValid(double coeff)
{
    return (isfinite(coeff) && !isnan(coeff));
}

bool IsError(ExitCode status)
{
    return (status != ExitCodeOK);
}

ExitCode FileInputCoeffs(FILE *fin_p, FILE *fout_p, struct EquationCoeffs *eq_ptr)
{
    if (fscanf(fin_p, "%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c) != 3)
    {
        return ExitCodeINPUT_ERROR;
    }
    return ExitCodeOK;
}

ExitCode FilePrintSolutions(FILE *fout_p, struct EquationRoots *roots_ptr)
{
    switch(roots_ptr->num_of_roots)
    {
        case NumOfRootsZERO:
        {
            fprintf(fout_p, "No solutions \n");
            break;
        }
        case NumOfRootsONE:
        {
            if (!IsValid(roots_ptr->x1))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            fprintf(fout_p, "One solution: %lg \n", roots_ptr->x1);
            break;
        }
        case NumOfRootsTWO:
        {
            if (!IsValid(roots_ptr->x1) || !IsValid(roots_ptr->x2))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            fprintf(fout_p, "First solution: %lg, second solution: %lg \n", roots_ptr->x1, roots_ptr->x2);
            break;
        }
        case NumOfRootsINF_SOLS:
        {
            fprintf(fout_p, "Any number \n");
            break;
        }
        case NumOfRootsNAN:
        {
            return ExitCodeSOLVER_ERROR;
        }
    }
    return ExitCodeOK;
}

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
        default:
        {
            fprintf(fout_p, "How did you get here? Everything is OK");
        }
    }
}

ExitCode InputCoeffs(struct EquationCoeffs *eq_ptr)
{
    printf("Enter coefficients of equation ax^2+bx+c=0 in format \"a b c\"\n");
    if (scanf("%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c) != 3)
    {
        return ExitCodeINPUT_ERROR;
    }
    printf("Your input: %lg % lg %lg \n", eq_ptr->a, eq_ptr->b, eq_ptr->c);
    return ExitCodeOK;
}

ExitCode PrintSolutions(struct EquationRoots *roots_ptr)
{
    switch(roots_ptr->num_of_roots)
    {
        case NumOfRootsZERO:
        {
            printf("No solutions \n");
            break;
        }
        case NumOfRootsONE:
        {
            if (!IsValid(roots_ptr->x1))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            printf("One solution: %lg \n", roots_ptr->x1);
            break;
        }
        case NumOfRootsTWO:
        {
            if (!IsValid(roots_ptr->x1) || !IsValid(roots_ptr->x2))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            printf("First solution: %lg, second solution: %lg \n", roots_ptr->x1, roots_ptr->x2);
            break;
        }
        case NumOfRootsINF_SOLS:
        {
            printf("Any number \n");
            break;
        }
        case NumOfRootsNAN:
        {
            return ExitCodeSOLVER_ERROR;
        }
    }
    return ExitCodeOK;
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
        default:
        {
            printf("How did you get here? Everything is OK \n");
        }
    }
}
