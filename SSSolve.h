#ifndef SSSOLVE_H
#define SSSOLVE_H

#include "SSStructures.h"
#include "SSErrorCodes.h"

ExitCode SolveQuadEquation(EquationCoeffs *eq_ptr, EquationRoots *roots_ptr);
bool RootsEqual(EquationRoots *roots1_ptr, EquationRoots *roots2_ptr); // Is
bool IsValid(double coeff);
bool IsZero(double coeff);

#endif
