#ifndef SSUNITTEST_H
#define SSUNITTEST_H
#include <stdio.h>
#include "SSErrorCodes.h"

ExitCode RunUnitTests();
bool IsFloatsEqual(double a, double b);
bool IsRootsEqual(EquationRoots *roots1_ptr, EquationRoots *roots2_ptr);

#endif
