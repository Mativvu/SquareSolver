#ifndef SSUNITTEST_H
#define SSUNITTEST_H
#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"

ExitCode RunUnitTests();
ExitCode FileRunUnitTests();
bool IsFloatsEqual(double a, double b);
bool IsRootsEqual(EquationRoots *roots1_ptr, EquationRoots *roots2_ptr);
ExitCode FileInputTestAnswers(FILE *fin_p, EquationRoots *roots_ptr);
ExitCode FileInputNumOfTests(FILE *fin_coeffs_p, int *num_of_tests);

#endif
