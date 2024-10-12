/*!
* \file
* \brief Algorithm of solving quadratic equations
* and functions of validating coeffecients.
*/
#ifndef SOLVE_H
#define SOLVE_H

#include "Structures.h"
#include "ErrorCodes.h"

bool IsZero(double number);
/** \fn IsZero(double number)
* \brief Checks if the value of the number is zero.
*
* \details Checks if the fabs() value of the number is less than ::EPS,
* this method is used to work with floating numbers.
*
* @param number Number you want to know is zero or not.
*
* @return 1 if zero, 0 if not zero)
*/

bool IsValid(double number);
/** \fn IsValid(double number)
* \brief Checks if the number is valid for calculations.
*
* \details Compares number with NAN and INF constants.
*
* @return 0 if NAN or INF, 1 otherwise
*/

ExitCode SolveQuadEquation(const EquationCoeffs *eq_ptr, EquationRoots *roots_ptr);
/** \fn SolveQuadEquation(EquationCoeffs *eq_ptr, EquationRoots *roots_ptr)
* \brief Algorithm of solving quadratic equations.
*
* \details Uses coefficients from EquationCoeffs and writes number of solutions
* and roots in EquationRoots.
* - This function calls:
*       - ::IsValid() to check if coefficients are valid or not before any calculations.
*       - sqrt() from <math.h> library to calculate square root of number.
*
* Assigns a certain ::NumOfRoots value to num_of_roots variable from EquationRoots
* to prevent impossible values.
*
* @param eq_ptr Pointer to EquationCoeffs to get coefficients for equation from.
* @param roots_ptr Pointer to EquationRoots to assign solutions and number of roots to.
*
* @throw ::ExitCodeCOEFF_ERROR if any of the coefficients is not valid.
*
* @return ::ExitCodeOK if finished with no errors.
*/

#endif //SOLVE_H
