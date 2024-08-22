#ifndef SSSOLVE_H
#define SSSOLVE_H
#include "SSStructures.h"
#include "SSErrorCodes.h"

bool IsZero(double coeff);
bool IsValid(double coeff);
ExitCode SolveQuadEquation(EquationCoeffs *eq_ptr, EquationRoots *roots_ptr);

#endif
