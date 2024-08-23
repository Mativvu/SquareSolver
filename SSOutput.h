#ifndef SSOUTPUT_H
#define SSOUTPUT_H
#include <stdio.h>
#include "SSStructures.h"
#include "SSErrorCodes.h"

extern const char* RED;
extern const char* GREEN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* MAGENTA;
extern const char* CYAN;
extern const char* RESET;

void ColorPrintf(const char *color, const char *format, ...);
ExitCode PrintSolutions(EquationRoots *roots_ptr);
ExitCode FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr);

#endif
