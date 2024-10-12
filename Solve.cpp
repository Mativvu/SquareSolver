#include <math.h>

#include "ErrorCodes.h"
#include "Structures.h"
#include "Debug.h"
#include "Solve.h"

const double EPS = 1e-9;

bool IsZero(double number)
{
    return (fabs(number) < EPS);
}

bool IsValid(double number)
{
    return (isfinite(number) && !isnan(number));
}

ExitCode SolveQuadEquation(const EquationCoeffs *eq_ptr, EquationRoots *roots_ptr)
{
    DEBUGMyAssert(eq_ptr != NULL);
    DEBUGMyAssert(roots_ptr != NULL);

    double a = eq_ptr->a;
    double b = eq_ptr->b;
    double c = eq_ptr->c;

    if (!(IsValid(a) && IsValid(b) && IsValid(c)))
    {
        return ExitCodeCOEFF_ERROR;
    }

    if (IsZero(a))
    {
        if (IsZero(b))
        {
            roots_ptr->num_of_roots = (IsZero(c)) ? NumOfRootsINF_SOLS
                                                  : NumOfRootsZERO;
            DEBUGPrintEquation("c = 0");
        }
        else
        {
            roots_ptr->x1 = (IsZero(c)) ? 0
                                        : -(c/b);
            roots_ptr->num_of_roots = NumOfRootsONE;
            DEBUGPrintEquation("bx+c = 0");
        }
    }
    else // (a != 0)
    {
        if (IsZero(b) && c/a > EPS)
        {
            double sqrt_ca = sqrt(c/a);
            roots_ptr->x1 = sqrt_ca;
            roots_ptr->x2 = -sqrt_ca;
            roots_ptr->num_of_roots = NumOfRootsTWO;
            DEBUGPrintEquation("ax^2+c = 0");
        }
        else
        {
            double D = b*b - 4*a*c;
            double sqrt_D = sqrt(D);
            if (IsZero(D))
            {
                roots_ptr->x1 = -b/(2*a);
                roots_ptr->num_of_roots = NumOfRootsONE;
                DEBUGPrintEquation("ax^2+bx+c = 0, D=0");
            }
            else if (D > EPS)
            {
                roots_ptr->x1 = (-b + sqrt_D)/(2*a);
                roots_ptr->x2 = (-b - sqrt_D)/(2*a);
                roots_ptr->num_of_roots = NumOfRootsTWO;
                DEBUGPrintEquation("ax^2+bx+c = 0, D>0");
            }
            else
            {
                roots_ptr->num_of_roots = NumOfRootsZERO;
                DEBUGPrintEquation("ax^2+bx+c = 0, D<0");
            }
        }
    }
    return ExitCodeOK;
}
