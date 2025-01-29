#include "fileprocessing.h"
#include "utilities.h"

void processFilterFile(const char* filename, short int* parameter, short int* parameters, int* flag)
{
    if (filename == NULL)
    {
        printf("No config file provided.\n");
        return;
    }

    printf("Filename: (%s)\n", filename);
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

        printf("(%s)\n", act);
        *flag = processArgument(act, parameter, parameters, flag);


        printf("Line: (%s)\n", line);
    }


    fclose(configFile);

    return;
}

/*
int procesarArchivoConf(int argc, char* argv[], int comandos[], int parametros[], char* nombreArchFiltros, char* nombreArchErrores)
{
    FILE* archivo = fopen(nombreArchFiltros, "rb");

    if (!archivo)
    {
        return 1;
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {

        char* act = strchr(linea, '\n');

        if (act) *act = '\0';

        act = strchr(linea, '\r');
        if (act) *act = '\0';

        char* parametro = strchr(linea, '=');
        char* filtro = linea;

        if (parametro)
        {
            *parametro = '\0';
            parametro++;
        }


        int indice = obtenerIndiceComando(filtro);
        int comandoInvalido = validarComandoInformarError(nombreArchErrores, atoi(parametro), filtro, indice);

        if (!comandoInvalido)
        {
            comandos[indice] = 1;

            if (parametro && *parametro)
            {
                int valor = atoi(parametro);
                parametros[indice] = valor > -1 ? valor : -1;
            }
        }


    }

    fclose(archivo);

    return OK;
}*/
