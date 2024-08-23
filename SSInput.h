#ifndef SSINPUT_H
#define SSINPUT_H
#include <stdio.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"

ExitCode InputCoeffs(EquationCoeffs *eq_ptr);
ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr);
ExitCode FileReadLine(FILE *fin_p, char *line);

#endif
