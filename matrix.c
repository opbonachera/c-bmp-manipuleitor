#include "matrix.h"
#include "constantes.h"

void** initMatrix(int rows, int columns, size_t elementSize)
{
    void** matrix = malloc(rows * sizeof(void*));
    if (!matrix)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(columns * elementSize);
        if (!matrix[i])
        {
            destroyMatrix(rows, matrix, elementSize);
            return NULL;
        }
    }

    return matrix;
}

int destroyMatrix(int rows, void** matrix, size_t elementSize)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
    return OK;
}


int matrixFromFile(int rows, int columns, FILE* file, t_pixel** matrix)
{
    for(int i=0; i<rows; i++)
    {
        fread(matrix[i], sizeof(t_pixel), columns, file);
    }

    return OK;
}
