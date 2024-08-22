#ifndef SSSDEBUG_H
#define SSSDEBUG_H

//#define DEBUG
#define UNITEST
#define FILEMODE

extern const char* ANSI_COLOR_BLUE;
extern const char* ANSI_COLOR_RESET;

#ifdef DEBUG
#define DEBUGPrintStr(str) printf("%s%s%s \n", ANSI_COLOR_BLUE, str, ANSI_COLOR_RESET)
#define DEBUGPrintEquation(expr) printf("%sIdentified equation: " #expr "%s\n", \
                                        ANSI_COLOR_BLUE, ANSI_COLOR_RESET)
#define DEBUGMyAssert(expr)                                  \
if(!(expr))                                                  \
{                                                            \
    printf("Assert fail line %d, expr: " #expr " file %s",   \
    __LINE__, __FILE__);                                     \
    exit(1);                                                 \
}
#else
#define DEBUGPrintStr(str) ;
#define DEBUGPrintEquation(expr) ;
#define DEBUGMyAssert(expr) ;
#endif

#endif
