#ifndef SSSDEBUG_H
#define SSSDEBUG_H
#include "SSOutput.h"

//#define DEBUG

#ifdef DEBUG
#define DEBUGPrintStr(str) printf("%s%s%s \n", BLUE, str, RESET)
#define DEBUGPrintEquation(expr) printf("%sIdentified equation: " #expr "%s\n", \
                                        BLUE, RESET)
#define DEBUGMyAssert(expr)                                  \
if(!(expr))                                                  \
{                                                            \
    printf("Assert fail line %d, expr: " #expr " file %s",   \
    __LINE__, __FILE__);                                     \
    abort();                                                 \
}
#else
#define DEBUGPrintStr(str) ;
#define DEBUGPrintEquation(expr) ;
#define DEBUGMyAssert(expr) ;
#endif

#endif
