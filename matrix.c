#include "matrix.h"
#include "constantes.h"

void** initMatrix(int rows, int columns, size_t elementSize)
{
    void** matrix = malloc(rows * sizeof(void*));
    if (!matrix)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(elementSize * columns);
        if (!matrix[i])
        {
            destroyMatrix(matrix, i);
            return NULL;
        }
    }

    return matrix;
}


int destroyMatrix(void** matrix, int rows)
{
    void** last = matrix + (rows - 1);
    for(void** i = matrix; i<last; i++)
    {
        free(*i);
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
