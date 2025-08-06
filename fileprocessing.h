#ifndef FILE_PROCESSING_INCLUDED
#define FILE_PROCESSING_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "imagegeneration.h"


void processFilterFile(const char* filename, short int* parameter, short int* parameters, int* flag);
void  writeFile(FILE* archivo, t_pixel** mat, size_t filas, size_t columnas);
char* generateImageName(const char* filter,  char* fileName);
int   readHeader(FILE* file, t_header *header);

#endif // FILE_PROCESSING_INCLUDED
