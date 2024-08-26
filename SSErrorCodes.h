/*!
* \file
* \brief Enum ExitCode for errors that other functions return
* as "status" and functions to check if returned status is bad
* and to describe each error.
*/

/** \fn IsError(ExitCode status)
* \brief Checks if status is bad or good.
*
* \details Checks if status is bad or good.
*
* @param status ::ExitCode status that most functions return after finishing.
*
* @return 0 if status is ::ExitCodeOK and 1 otherwise
*/

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

#ifndef SSERRORCODES_H
#define SSERRORCODES_H

#include <stdio.h>

enum ExitCode {
    ExitCodeOK,               //0
    ExitCodeINPUT_ERROR,      //1
    ExitCodeCOEFF_ERROR,      //2
    ExitCodeSOLVER_ERROR,     //3
    ExitCodeOUTPUT_ERROR,     //4
    ExitCodeEND_TEST,         //5
    ExitCodeMAXLEN_REACHED,   //6
    ExitCodeUNKNOWN_ARG,      //7
    ExitCodeCOMMAND_ERROR,    //8
    ExitCodeFILE_ERROR,       //9
    ExitCodeDUPLICATION_ERROR //10
};

bool IsError(ExitCode status);
void DescribeError(ExitCode status);

#endif
