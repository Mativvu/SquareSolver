/*!
* \file
* \brief Functions to output data to file or stdout
* and to print colored text using constant ANSI color codes.
*/
#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

// TODO: Add color lib

#include "Structures.h"
#include "ErrorCodes.h"

const char* const RED    = "\x1b[31m";
const char* const GREEN  = "\x1b[32m";
const char* const YELLOW = "\x1b[33m";
const char* const BLUE   = "\x1b[34m";
const char* const MAGENTA= "\x1b[35m";
const char* const CYAN   = "\x1b[36m";
const char* const RESET  = "\x1b[0m";
#define _RED     "\x1b[31m"
#define _GREEN   "\x1b[32m"
#define _YELLOW  "\x1b[33m"
#define _BLUE    "\x1b[34m"
#define _MAGENTA "\x1b[35m"
#define _CYAN    "\x1b[36m"
#define _RESET   "\x1b[0m"

void ColorPrintf(const char *color, const char *format, ...);
/** \fn ColorPrintf(const char *color, const char *format, ...)
* \brief Function to print colored text using ANSI color codes.
*
* \details Can be called with variable list of arguments, resets the color
* back to normal after printing.
*
* @param color Name of the constant ANSI color code.
* @param format String literal, format of output of function printf().
* @param ... List of variables for printf output.
*/

ExitCode PrintSolutions(const EquationRoots *roots_ptr);
/** \fn PrintSolutions(EquationRoots *roots_ptr)
* \brief Prints solutions from EquationRoots to the stdout.
*
* \details Just calls ::FilePrintSolutions() with stdout as pointer to file.
*
* @param roots_ptr Pointer to EquationRoots to get number of roots and solutions from.
*
* @throw abort() if DEBUG mode is turned on and pointer roots_ptr is nullptr.
*
* @return ::FilePrintSolutions with file pointer as stdout.
*/

ExitCode FilePrintSolutions(FILE *fout_p, const EquationRoots *roots_ptr);
/** \fn FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr)
* \brief Prints solutions from EquationRoots into file.
*
* \details Prints different messages according to the value of num_of_roots in
* structure EquationRoots.
* - Calls ::IsValid() to check if solutions are valid numbers before printing them.
*
* @param fout_p Pointer to the file to print solutions in.
* @param roots_ptr Pointer to EquationRoots to get number of roots and solutions from.
*
* @throw abort() if DEBUG mode is on and either fout_p or roots_ptr is nullptr.
* @throw ::ExitCodeOUTPUT_ERROR if solutions are not valid numbers.
* @throw ::ExitCodeSOLVER_ERROR if number of roots is ::NumOfRootsNAN.
*
* @param fout_p Pointer to the file to print solutions into.
* @param roots_ptr Pointer to EquationRoots to get number of roots and solutions from.
*
* @return ::ExitCodeOK if finished with no errors.
*/

#endif //OUTPUT_H
