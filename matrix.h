#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "stdlib.h"
#include "stdio.h"

#include "constantes.h"

int     destroyMatrix(void** matrix, int rows);
int     matrixFromFile(int rows, int columns, FILE* file, t_pixel** matrix);
void**  initMatrix    (int rows, int columns, size_t elementSize);

#endif // UTILITIES_H_INCLUDED
