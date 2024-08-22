#ifndef SSOUTPUT_H
#define SSOUTPUT_H

#include <stdio.h>
#include "SSStructures.h"
#include "SSErrorCodes.h"

void COLOR_RED_printf(const char *str);
void COLOR_GREEN_printf(const char *str);
ExitCode PrintSolutions(EquationRoots *roots_ptr);
ExitCode FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr);

#endif
