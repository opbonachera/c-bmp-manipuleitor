#ifndef IMAGE_GENERATION_H_INCLUDED
#define IMAGE_GENERATION_H_INCLUDED

#include <stddef.h>
#include <stdio.h>

#include "constantes.h"
#include "estructuras.h"

int  bmpManipuleitor(int argc, char* argv[]);
int  readHeader(FILE* img, t_header* header);
void modificarDimensiones(FILE* img, int nuevoX, int nuevoY);
void generateImages(short int* flag, short int parameters[]);
void writeHeader(FILE* img, FILE* nueva, t_header* header);

#endif // IMAGE_GENERATION_H_INCLUDED
