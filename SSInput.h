/*!
* \file
* \brief Functions to input data from file or stdin and to read one
* line from stream/file.
*/

/** \fn InputCoeffs(EquationCoeffs *eq_ptr)
* \brief Function to input coefficients in EquationCoeffs.
*
* \details Prints some additional info for user, such as format of input
* and recieved values. Reads 3 values from stream to assign coefficients.
* - Calls ::FileReadLine() with stdin as pointer to file to read one line of
* maximum length of ::MAXLEN from stream and put it in a buffer. The buffer
* is next used as string for sscanf() to read data from. This is done to
* prevent scanf() from skipping end of the line when there are less then
* 3 recieved values.
*
* @param eq_ptr Pointer to EquationCoeffs to assign values to.
*
* @throw abort() if DEBUG mode is on and eq_ptr is nullptr.
* @throw ::ExitCodeINPUT_ERROR if didn`t recieve exactly 3 values for coefficients.
*
* @return ::ExitCodeOK if finished with no errors.
*/

/** \fn FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr);
* \brief Function to input coefficients from file in EquationCoeffs.
*
* \details Reads 3 values from file to assign coefficients.
* - Calls ::FileReadLine() with pointer to file to read one line of maximum
* length of ::MAXLEN from file and put it in a buffer. The buffer is next
* used as string for sscanf() to read data from. This is done to prevent
* scanf() from skipping end of the line when there are less then 3 recieved
* values.
*
* @param fin_p Pointer to file to read values from.
* @param eq_ptr Pointer to EquationCoeffs to assign values to.
*
* @throw abort() if DEBUG mode is on and eq_ptr or fin_p is nullptr.
* @throw ::ExitCodeINPUT_ERROR if didn`t recieve exactly 3 values for coefficients.
*
* @return ::ExitCodeOK if finished with no errors.
*/

/** \fn FileReadLine(FILE *fin_p, char line[]);
* \brief Reads one line from file.
*
* \details Reads line of maximum length of ::MAXLEN one char at a time
* using getc() function.
*
* @param fin_p Pointer to file to read one line from.
* @param line Pointer to array of chars to put chars into.
*
* @throw abort() when DEBUG mode is on and fin_p is nullptr.
* @throw ::ExitCodeMAXLEN_REACHED when line has more than ::MAXLEN characters.
*
* @return ::ExitCodeOK when finished with no errors.
*/

#ifndef SSINPUT_H
#define SSINPUT_H

#include <stdio.h>

#include "SSErrorCodes.h"
#include "SSStructures.h"

const int MAXLEN = 100;

ExitCode InputCoeffs(EquationCoeffs *eq_ptr);
ExitCode FileInputCoeffs(FILE *fin_p, EquationCoeffs *eq_ptr);
ExitCode FileReadLine(FILE *fin_p, char line[]);

#endif
