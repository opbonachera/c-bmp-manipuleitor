#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char*  getArgument(const char* argument, const char* separator);
int    checkArgumentType(char* argument, char* separator);
int    getParameter(char* parameter);
int    processArgument(char* argument, short int parameter, short int parameters[], short int* flag);
int    truncate(int intg);

#endif // UTILITIES_H_INCLUDED
