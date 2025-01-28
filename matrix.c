#include "matrix.h"
#include "constantes.h"

void** initMatrix    (int rows, int columns, size_t elementSize)
{
    void** matrix = malloc(rows * sizeof(void*));

    if(!matrix)
    {
        return ERROR_ALLOCATING_MEMORY;
    }

    void** lastElement = (rows + matrix);

    for(void** i=matrix; i < lastElement; i+= sizeof(void*))
    {
        *i = malloc(elementSize * columns);

        if(!*i)
        {
            /*destroyMatrix(matrix, rows, elementSize);
            return ERROR_ALLOCATING_MEMORY; */
        }

    }

    return matrix;
}

int destroyMatrix(int rows, void** matrix, size_t elementSize)
{
    void** lastElement = (rows + matrix);

    for(void** i=matrix; i < lastElement; i+= sizeof(void*))
    {
        free(*i);
    }

    free(*matrix);

    return OK;
}


int matrixFromFile(int rows, int columns, FILE* file, t_pixel** matrix)
{
    for(int i=0; i<rows; i++)
    {
        fread(&matrix[i], sizeof(t_pixel), columns, file);
    }

    return OK;
}

