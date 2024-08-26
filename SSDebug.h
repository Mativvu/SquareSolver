/*!
* \file
* \brief Contains macros for debugging: printing strings,
* printing identified equation and handmade assert.
* Functions print colored text, see ::SSOutput.h for all color codes.
* You can switch debug mode by commenting "#define DEBUG".
*/

/** \def DEBUGPrintStr(str)
* \brief Function for printing(blue) one string.
*
* @param str String or string literal
*/

/** \def DEBUGPrintEquation(expr)
* \brief Function to print(blue) what kind of equation the algorithm identified.
*
* @param expr String literal
*/

/** \def DEBUGMyAssert(expr)
* \brief Works the same as usual assert but also prints(red) function prototype
*
* @param expr Comparing expression
*
* @throw abort() if expr is false.
*/

#ifndef SSSDEBUG_H
#define SSSDEBUG_H

#include <stdlib.h>

#include "SSOutput.h"

#define DEBUG

#ifdef DEBUG

#define DEBUGPrintStr(str)       printf("%s%s%s \n", BLUE, str, RESET)

#define DEBUGPrintEquation(expr) printf("%sIdentified equation: " #expr "%s\n", BLUE, RESET)

#define DEBUGMyAssert(expr)                                 \
    if(!(expr))                                             \
    {                                                       \
        printf("Assert fail expr: " #expr "\n"              \
               "line %d \nfunction: %s \nfile %s\n",        \
               __LINE__, __PRETTY_FUNCTION__, __FILE__);    \
        abort();                                            \
    }

#else
#define DEBUGPrintStr(str) ;
#define DEBUGPrintEquation(expr) ;
#define DEBUGMyAssert(expr) ;
#endif

#endif
