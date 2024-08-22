#include <stdio.h>
#include "SSStructures.h"
#include "SSErrorCodes.h"
#ifndef SSOUTPUT_H
#define SSOUTPUT_H

ExitCode PrintSolutions(EquationRoots *roots_ptr);
ExitCode FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr);

#endif
