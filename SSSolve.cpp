#include <stdio.h>
#include <math.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"
#include "SSDebug.h"
#include "SSSolve.h"

const double EPS = 1e-9;

bool IsZero(double coeff)
{
    return (fabs(coeff) < EPS);
}

bool IsValid(double coeff)
{
    return (isfinite(coeff) && !isnan(coeff));
}

ExitCode SolveQuadEquation(EquationCoeffs *eq_ptr, EquationRoots *roots_ptr)
{
    DEBUGMyAssert(eq_ptr != NULL);
    DEBUGMyAssert(roots_ptr != NULL);

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
            DEBUGPrintEquation("c = 0");
            roots_ptr->num_of_roots = (IsZero(c)) ? NumOfRootsINF_SOLS : NumOfRootsZERO;
        }
        else
        {
            DEBUGPrintEquation("bx+c = 0");
            roots_ptr->x1 = (IsZero(c)) ? 0 : -(c/b);
            roots_ptr->num_of_roots = NumOfRootsONE;
        }
    }
    else
    {
        if (IsZero(b) && c/a > EPS)
        {
            double sqrt_ca = sqrt(c/a);
            DEBUGPrintEquation("ax^2+c = 0");
            roots_ptr->x1 = sqrt_ca;
            roots_ptr->x2 = -sqrt_ca;
            roots_ptr->num_of_roots = NumOfRootsTWO;
        }
        else
        {
            double D = b*b - 4*a*c;
            double sqrt_D = sqrt(D);
            if (IsZero(D))
            {
                DEBUGPrintEquation("ax^2+bx+c = 0, D=0");
                roots_ptr->x1 = -b/(2*a);
                roots_ptr->num_of_roots = NumOfRootsONE;
            }
            else if (D > EPS)
            {
                DEBUGPrintEquation("ax^2+bx+c = 0, D>0");
                roots_ptr->x1 = (-b + sqrt_D)/(2*a);
                roots_ptr->x2 = (-b - sqrt_D)/(2*a);
                roots_ptr->num_of_roots = NumOfRootsTWO;
            }
            else
            {
                DEBUGPrintEquation("ax^2+bx+c = 0, D<0");
                roots_ptr->num_of_roots = NumOfRootsZERO;
            }
        }
    }
    return ExitCodeOK;
}
