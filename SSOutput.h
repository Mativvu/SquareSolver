#ifndef SSOUTPUT_H
#define SSOUTPUT_H
#include <stdio.h>
#include "SSStructures.h"
#include "SSErrorCodes.h"

const char* const RED    = "\x1b[31m";
const char* const GREEN  = "\x1b[32m";
const char* const YELLOW = "\x1b[33m";
const char* const BLUE   = "\x1b[34m";
const char* const MAGENTA= "\x1b[35m";
const char* const CYAN   = "\x1b[36m";
const char* const RESET  = "\x1b[0m";

void ColorPrintf(const char *color, const char *format, ...);
ExitCode PrintSolutions(EquationRoots *roots_ptr);
ExitCode FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr);

#endif
