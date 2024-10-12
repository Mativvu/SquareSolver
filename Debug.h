/*!
* \file
* \brief Contains macros for debugging: printing strings,
* printing identified equation and handmade assert.
* Functions print colored text, see \ref SSOutput.h for all color codes.
* You can switch debug mode by commenting "#define DEBUG".
*/

/** \def DEBUGPrintStr(str)
* \brief Function for printing one string in blue.
*
* \details Function for printing one string in blue.
*
* @param str String or string literal
*/

/** \def DEBUGPrintEquation(expr)
* \brief Function to print what kind of equation the algorithm identified in blue.
*
* \details Function to print what kind of equation the algorithm identified in blue.
*
* @param expr String literal
*/

/** \def DEBUGMyAssert(expr)
* \brief Works the same as usual assert but also prints function prototype.
* Prints in blue.
*
* \details Works the same as usual assert but also prints function prototype.
* Prints in blue.
*
* @param expr Comparing expression
*
* @throw abort() if expr is false.
*/

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#include "Output.h"

#define DEBUG

#ifdef DEBUG

#define DEBUGPrintStr(str) \
    printf("%s%s%s \n", BLUE, str, RESET);

#define DEBUGPrintEquation(expr) \
    printf("%sIdentified equation: " #expr "%s\n", BLUE, RESET);

#define DEBUGMyAssert(expr)                                 \
    if(!(expr))                                             \
    {                                                       \
        printf("%sAssert fail expr: " #expr "\n"            \
               "line %d \nfunction: %s \nfile %s%s\n",      \
               BLUE, __LINE__, __PRETTY_FUNCTION__,         \
               __FILE__, RESET);                            \
        abort();                                            \
    };

#else
#define DEBUGPrintStr(str) ;
#define DEBUGPrintEquation(expr) ;
#define DEBUGMyAssert(expr) ;
#endif //DEBUG

#endif //DEBUG_H
