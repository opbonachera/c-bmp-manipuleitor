#include "fileprocessing.h"
#include "utilities.h"

void processFilterFile(const char* filename, short int* parameter, short int* parameters, short int* flag)
{
    if (filename == NULL)
    {
        printf("No config file provided.\n");
        return;
    }

    FILE* configFile = fopen(filename, "rb");
    if (!configFile)
    {
        printf("Error opening config file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), configFile))
    {
        char* act = strchr(line, '\n');
        if (act) *act = '\0';

        act = strchr(line, '\r');
        if (act) *act = '\0';

        char* command = getArgument(line, "");
        short int parameter = getParameter(line);

        processArgument(command, parameter, parameters, flag);
    }

    fclose(configFile);

    return;
}

void writeFile(FILE* archivo, t_pixel** mat, size_t filas, size_t columnas)
{
    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<columnas; j++)
        {
            fwrite(mat[i][j].pixel, sizeof(t_pixel), 1, archivo);
        }
    }
}

char* generateImageName(const char* filter,  char* fileName)
{
    char* nombreNuevoArchivo = malloc(strlen(filter) + 1 + strlen(fileName) + 1);
    if (!nombreNuevoArchivo)
    {
        return NULL;
    }

    strcat(nombreNuevoArchivo, filter);
    strcat(nombreNuevoArchivo, "_");
    strcat(nombreNuevoArchivo, fileName);

    return nombreNuevoArchivo;
}
