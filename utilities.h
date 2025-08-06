#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char*  getArgument(const char* argument, const char* separator);
char*  getNewFilename(const char* firstFile, const char* secondFile, const char* filterName, const char* extension);
int    checkArgumentType(char* argument, char* separator);
int    getParameter(char* parameter);
int    processArgument(char* argument, short int parameter, short int parameters[], int* flag);
int    truncate(int intg);
int    processCommandLine(const int argc, char* argv[], short int* parameters, char* imageFiles[], char* filterFile[], int* flag);

#endif // UTILITIES_H_INCLUDED
