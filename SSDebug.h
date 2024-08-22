#ifndef SSSDEBUG_H
#define SSSDEBUG_H

#define DEBUG
#define UNITEST
#define FILEMODE

//#define COLOR_RED_Print(X) printf("%s %s %s",ANSI_COLOR_RED,X,ANSI_COLOR_RESET)

#ifdef DEBUG
#define DEBUGPrintStr(string) printf("%s \n",string)
#define DEBUGPrintEquation(expr) printf("Identified equation: " #expr "\n")
#define DEBUGMyAssert(expr)                                  \
if(!(expr))                                                  \
{                                                            \
    printf("Assert fail line %d, expr: " #expr " file %s",   \
    __LINE__, __FILE__);                                     \
    exit(1);                                                 \
}
#else
#define DEBUGPrintStr(string) ;
#define DEBUGPrintEquation(expr) ;
#define DEBUGMyAssert(expr) ;
#endif

#endif
