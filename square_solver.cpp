#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "SQ_header.h"

enum ExitCode
{
    OK,
    INPUT_ERROR,
    COEFF_ERROR,
    SOLVER_ERROR,
    OUTPUT_ERROR,
};

enum NumOfRoots
{
    ZERO,
    ONE,
    TWO,
    INF_SOLS,
    NumOfRootsNAN
};

const double EPS = 1e-9;

struct EquationCoeffs { //ax^2+bx+c=0
    double a, b, c;
};


struct EquationRoots {
    NumOfRoots num_of_roots;
    double x1, x2;
};

ExitCode InputCoeffs(struct EquationCoeffs *eq_ptr);
ExitCode SolveQuadEquation(struct EquationCoeffs *eq_ptr, struct EquationRoots *roots_ptr);
ExitCode PrintSolutions(struct EquationRoots *roots_ptr);
void DiscribeError(ExitCode status);
bool IsValid(double coeff);
bool IsZero(double coeff);
bool IsError(ExitCode status);

int main()
{
    struct EquationCoeffs equation = {NAN, NAN, NAN};
    struct EquationRoots roots = {NumOfRootsNAN, NAN, NAN};
    ExitCode status = OK;

    status = InputCoeffs(&equation);
    if (IsError(status))
    {
        DiscribeError(status);
        return status;
    }
    status = SolveQuadEquation(&equation, &roots);
    if (IsError(status))
    {
        DiscribeError(status);
        return status;
    }
    status = PrintSolutions(&roots);
    if (IsError(status))
    {
        DiscribeError(status);
        return status;
    }
}

ExitCode SolveQuadEquation(struct EquationCoeffs *eq_ptr, struct EquationRoots *roots_ptr)
{
    double a = eq_ptr->a;
    double b = eq_ptr->b;
    double c = eq_ptr->c;

    if(!(IsValid(a) && IsValid(b) && IsValid(c)))
    {
        return COEFF_ERROR;
    }

    if (IsZero(a)) // bx+c=0
    {
        if (IsZero(b)) // c = 0
        {
            roots_ptr->num_of_roots = (IsZero(c)) ? INF_SOLS : ZERO;
        }
        else // bx+c=0
        {
            roots_ptr->x1 = (IsZero(c)) ? 0 : -(c/b);
            roots_ptr->num_of_roots = ONE;
        }
    }
    else // ax^2+bx+c=0
    {
        // sqrt_D
        if (IsZero(b) && c < -EPS) // ax^2+c=0
        {
            roots_ptr->x1 = sqrt(c/a);
            roots_ptr->x2 = -sqrt(c/a);
            roots_ptr->num_of_roots = TWO;
        }
        else // ax^2+bx+c=0
        {
            double D = b*b - 4*a*c;
            double sqrt_D = sqrt(D);
            if (IsZero(D)) // ax^2+bx=0
            {
                roots_ptr->x1 = -b/(2*a);
                roots_ptr->num_of_roots = ONE;
            }
            else if (D > EPS) //ax^2+bx+c=0
            {
                roots_ptr->x1 = (-b + sqrt_D)/(2*a);
                roots_ptr->x2 = (-b - sqrt_D)/(2*a);
                roots_ptr->num_of_roots = TWO;
            }
            else //D < 0
            {
                roots_ptr->num_of_roots = ZERO;
            }
        }
    }
    return OK;
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
    return (status != OK);
}

ExitCode InputCoeffs(struct EquationCoeffs *eq_ptr)
{
    printf("Enter coefficients of equation ax^2+bx+c=0 in format \"a b c\"\n");
    if (scanf("%lg %lg %lg", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c) != 3)
    {
        return INPUT_ERROR;
    }
    printf("Your input: %lg % lg %lg \n", eq_ptr->a, eq_ptr->b, eq_ptr->c);
    return OK;
}

ExitCode PrintSolutions(struct EquationRoots *roots_ptr)
{
    switch(roots_ptr->num_of_roots)
    {
        case ZERO:
        {
            printf("No solutions \n");
            break;
        }
        case ONE:
        {
            if (!IsValid(roots_ptr->x1))
            {
                return OUTPUT_ERROR;
            }
            printf("One solution: %lg \n", roots_ptr->x1);
            break;
        }
        case TWO:
        {
            if (!IsValid(roots_ptr->x1) || !IsValid(roots_ptr->x2))
            {
                return OUTPUT_ERROR;
            }
            printf("First solution: %lg, second solution: %lg \n", roots_ptr->x1, roots_ptr->x2);
            break;
        }
        case INF_SOLS:
        {
            printf("Any number \n");
            break;
        }
        case NumOfRootsNAN:
        {
            return SOLVER_ERROR;
        }
    }
    return OK;
}

void DiscribeError(ExitCode status)
{
    switch (status)
    {
        case INPUT_ERROR:
        {
            printf("Wrong input, try again \n");
            break;
        }
        case COEFF_ERROR:
        {
            printf("Coefficients are not valid, enter again \n");
            break;
        }
        case SOLVER_ERROR:
        {
            printf("Number of roots is not valid \n");
            break;
        }
        case OUTPUT_ERROR:
        {
            printf("Error, solution is NaN \n");
            break;
        }
        default:
        {
            printf("How did you get here? Everything is OK");
        }
    }
}
