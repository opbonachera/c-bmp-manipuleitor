#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "stdlib.h"
#include "stdio.h"

#include "estructuras.h"

int     destroyMatrix (int rows, void** matrix, size_t elementSize);
int     matrixFromFile(int rows, int columns, FILE* file, t_pixel** matrix);
void**  initMatrix    (int rows, int columns, size_t elementSize);


#endif // UTILITIES_H_INCLUDED
