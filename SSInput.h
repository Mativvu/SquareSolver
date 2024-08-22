#ifndef SSINPUT_H
#define SSINPUT_H
#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"

ExitCode InputCoeffs(EquationCoeffs *eq_ptr);
ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr);
ExitCode FileInputTestAnswers(FILE *fin_p, EquationRoots *roots_ptr); //Unit
ExitCode FileReadLine(FILE *fin_p, char *line);
ExitCode FileInputNumOfTests(FILE *fin_coeffs_p, int *num_of_tests); //Unit

#endif
