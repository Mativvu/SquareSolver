#ifndef SSSDEBUG_H
#define SSSDEBUG_H

#ifdef DEBUG
#define DEBUGPrintStr(string) printf(string)
#define DEBUGPrintEquation(expr) printf("Identified equation: " #expr "\n")
#define DEBUGMyAssert(expr)                            \
if(!(expr))                                            \
{                                                      \
    printf("Assert fail line %d, expr: " #expr " file %s",   \
    __LINE__, __FILE__);                               \
    exit(1);                                           \
}
#else
#define DEBUGPrintStr(string) ;
#define DEBUGPrintEquation(expr) ;
#define DEBUGMyAssert(expr) ;
#endif

#endif
