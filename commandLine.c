#include "commandLine.h"
#include "utilities.h"
#include "imagegeneration.h"
#include "constantes.h"


int processCommandLine(const int argc, char* argv[], short int* parameters, char* imageFiles[], char* filterFile[], int* flag)
{
    for (int i = 1; i < argc; i++)
    {
        if(checkArgumentType(argv[i], "--"))
        {
            char* command = getArgument(argv[i], "--");

            short int parameter = getParameter(argv[i]);

            processArgument(command, parameter, parameters, flag);

        }

        if (checkArgumentType(argv[i], ".bmp"))
        {
            if (!imageFiles[0])
                imageFiles[0] = argv[i];
            else if (!imageFiles[1])
                imageFiles[1] = argv[i];
            else
                printf("Only two image files allowed.\n");
        }

        if (checkArgumentType(argv[i], ".txt"))
        {
            if (*filterFile == NULL)
                *filterFile = argv[i];

            else
                printf("Only one filter file allowed.\n");
        }
    }

    return 0;
}
