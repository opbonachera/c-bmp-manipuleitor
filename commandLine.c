#include "commandLine.h"

// processCommandLine(argc, argv, &parameters, &imageFiles, &configFiles, &flag);

int processCommandLine(const int argc, char* argv[], int* parameters, char* imageFiles[], char* configFiles[], int* flag)
{
    for (int i = 0; i < argc; i++)
    {
        // Check for command arguments with "--"
        if (checkArgumentType(argv[i], "--"))
        {
            char* command = getArgument(argv[i], "--");
            if (!command)
            {
                printf("Failed to process argument: %s\n", argv[i]);
                continue;
            }

            short int parameter = getParameter(argv[i]);

            // Corrected: Update the value of flag through its pointer
            *flag = processArgument(command, &parameter, parameters, *flag);

            free(command);
        }

        // Check for image files
        if (checkArgumentType(argv[i], ".bmp"))
        {
            if (!imageFiles[0])
                imageFiles[0] = argv[i]; // Corrected to use imageFiles as an array of pointers
            else if (!imageFiles[1])
                imageFiles[1] = argv[i];
            else
                printf("Only two image files allowed.\n");
        }

        // Check for config files
        if (checkArgumentType(argv[i], ".txt"))
        {
            if (!configFiles[0])
                configFiles[0] = argv[i]; // Corrected to use configFiles as an array of pointers
            else
                printf("Only one config file allowed.\n");
        }
    }

    return 0;
}
