#ifndef FILE_PROCESSING_INCLUDED
#define FILE_PROCESSING_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "imagegeneration.h"


void processFilterFile(const char* filename, short int* parameter, short int* parameters, int* flag);

#endif // FILE_PROCESSING_INCLUDED
