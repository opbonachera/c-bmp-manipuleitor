#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

int     checkArgumentType(char* argument, char* separator);
int     getParameter(char* parameter);
char*   getArgument(const char* argument, const char* separator);

#endif // UTILITIES_H_INCLUDED
