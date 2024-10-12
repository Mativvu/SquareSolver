/*!
* \file
* \brief Enum ::ExitCode for errors that other functions return
* as "status" and functions to check if returned status is bad
* and to describe each error. Uses colored output, see \ref SSOutput.h
* for all color codes.
*/
#ifndef ERRORCODES_H
#define ERRORCODES_H

enum ExitCode {
    ExitCodeOK                = 0, /**< Function finished without errors. */
    ExitCodeINPUT_ERROR       = 1, /**< The input was wrong. */
    ExitCodeCOEFF_ERROR       = 2, /**< Coefficient was invalid number. */
    ExitCodeSOLVER_ERROR      = 3, /**< Error in SolveQuadEquation function. */
    ExitCodeOUTPUT_ERROR      = 4, /**< Trying to print invalid solutions. */
    ExitCodeEND_TEST          = 5, /**< Unit testing finished. */
    ExitCodeMAXLEN_REACHED    = 6, /**< Too many characters in one line. */
    ExitCodeUNKNOWN_ARG       = 7, /**< Found unknown argument. */
    ExitCodeCOMMAND_ERROR     = 8, /**< Forbidden combination of flags was typed. */
    ExitCodeFILE_ERROR        = 9, /**< Cannot open/find file. */
    ExitCodeDUPLICATION_ERROR = 10,/**< Identical flags were typed. */
    ExitCodeHELP_FLAG         = 11 /**< "--help" command was typed, stops program. */
};

bool IsError(ExitCode status);
/** \fn IsError(ExitCode status)
* \brief Checks if status is bad or good.
*
* \details Checks if status is bad or good.
*
* @param status ::ExitCode status that most functions return after finishing.
*
* @return 0 if status is ::ExitCodeOK and 1 otherwise
*/

void DescribeError(ExitCode status);
/** \fn DescribeError(ExitCode status)
* \brief Describes each error.
*
* \details Describes each error and returns error code in main function, then
* program finishes.
*
* @param status ::ExitCode status that most functions return after finishing.
*
* @return Any kind of ::ExitCode error that is recieved as argument.
*/

#endif //ERRORCODES_H
