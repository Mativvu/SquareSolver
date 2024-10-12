/*!
* \file
* \brief Functions to run unit tests using data from files or
* arrays of structures EquationCoeffs and EquationRoots,
* to input test data and number of tests and to compare calculated
* roots with answers. Uses colored output, see \ref SSOutput.h for color codes.
*/
#ifndef UNITTEST_H
#define UNITTEST_H

#include "ErrorCodes.h"
#include "Structures.h"
#include <stdio.h>

ExitCode RunUnitTests();
/** \fn RunUnitTests()
* \brief Function to run unit tests using data from internal arrays.
*
* \details Creates structures for coefficients, roots and answers.
* - Calls ::SolveQuadEquation() to calculate solutions.
*
* Prints when each test passes and calculated and expected roots
* when test fails. In the end prints how many tests passed, how many failed and
* percent of right answers. After finishing program ends with error 5(Testing finished).
*
* @throws ::ExitCodeSOLVER_ERROR when coefficients are invalid.
*
* @return ::ExitCodeEND_TEST status when finished with no errors.
*/
ExitCode FileRunUnitTests();
/** \fn FileRunUnitTests()
* \brief Function to run unit tests from files "UnitTestsInput.txt" and "UnitTestsOutput.txt".
*
* \details Opens file "UnitTestsInput.txt" with coefficients and "UnitTestAnswers.txt"
* with right solutions. Creates structures for coefficients, roots and answers.
* - This function also calls:
*         - ::FileInputCoeffs() to input coefficients.
*         - ::FileInputTestAnswers() to input solutions.
*         - ::SolveQuadEquation() to calculate solutions.
*         - ::IsRootsEqual() to compare solutions.
*
* Prints "Test x passed" when test passes and calculated and expected roots
* when test fails. In the end prints how many tests passed, how many failed and
* percent of right answers. After finishing program ends with error 5(Testing finished).
*
* @throws ::ExitCodeFILE_ERROR when cannot open/find files.
*
* @return ::ExitCodeEND_TEST status when finished with no errors.
*/
ExitCode FileInputTestAnswers(FILE *fin_answers_p, EquationRoots *roots_ptr);
/** \fn FileInputTestAnswers(FILE *fin_answers_p, EquationRoots *roots_ptr)
* \brief Assigns values from file "UnitTestsAnswers.txt" to EquationRoots structure.
*
* \details Reads a line from file "UnitTestsAnswers.txt" using ::FileReadLine()
* and scans number of roots and two roots from this line. This is done to
* prevent scanf() from skipping end of the line when there are less than
* 3 recieved values.
*
* @param fin_answers_p Pointer to the file with tests answers.
* @param roots_ptr EquationRoots pointer to asssign values to it.
*
* @throw ::ExitCodeINPUT_ERROR if line doesn`t contain exactly 3 numbers.
*
* @return ::ExitCodeOK when finished with no errors.
*/
ExitCode FileInputNumOfTests(FILE *fin_coeffs_p, size_t *num_of_tests_p);
/** \fn FileInputNumOfTests(FILE *fin_coeffs_p, int *num_of_tests_p)
* \brief Reads one number from the first line of file "UnitTestsInput.txt".
*
* \details Reads a line from file "UnitTestsInput.txt" using ::FileReadLine()
* and scans one integer from this line. This is done to prevent scanf()
* from skipping end of the line when there are less than 3 recieved values.
*
* @param fin_coeffs_p Pointer to the file with tests coefficients.
* @param num_of_tests_p Pointer to integer num_of_tests to assign value to it.
*
* @throw ::ExitCodeINPUT_ERROR if line doesn`t contain 1 integer.
*
* @return ::ExitCodeOK when finished with no errors.
*/
bool IsFloatsEqual(double a, double b);
/** \fn IsFloatsEqual(double a, double b)
* \brief Compares two floating numbers using ::FLT_EPS.
*
* @param a First number.
* @param b Second number.
*
* @return 1 if both NaN or equal, 0 if not.
*/
bool IsRootsEqual(const EquationRoots *roots1_ptr, const EquationRoots *roots2_ptr);
/** \fn IsRootsEqual(EquationRoots *roots1_ptr, EquationRoots *roots2_ptr)
* \brief Compares two structures EquationRoots.
*
* \details Compares number of roots and solutions.
* - Calls ::IsFloatsEqual() to compare roots.
*
* @param roots1_ptr Pointer to first struct EquationRoots.
* @param roots2_ptr Pointer to second struct EquationRoots.
*
* @throw abort() if ::DEBUG mode is on and pointer is nullptr.
*
* @return 1 if number of roots and solutions are equal, 0 otherwise.
*/

#endif //UNITTEST_H
