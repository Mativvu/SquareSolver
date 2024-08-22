#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"
#ifndef SSINPUT_H
#define SSINPUT_H

ExitCode InputCoeffs(EquationCoeffs *eq_ptr);
ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr);
ExitCode FileInputTestAnswers(FILE *fin_p, EquationRoots *roots_ptr);

#endif
