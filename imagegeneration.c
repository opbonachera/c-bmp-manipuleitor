#include  "imagegeneration.h"
#include  "utilities.h"
#include  "commandLine.h"

#include "constantes.h"

int bmpManipuleitor(int argc, char* argv[])
{
    char* imageFiles[2] = {NULL};
    char* configFiles[1] = {NULL};

    short int parameters[8] = {0};
    short int flag = 0;

    processCommandLine(argc, argv, &parameters, &imageFiles, &configFiles, &flag);

    generateImages(flag, parameters);

    return OK;
}

void generateImages(short int flag, short int parameters[])
{
    if (flag & RED_TONE)
        printf("Red tone is enabled with parameter %hd\n", parameters[1]);
    if (flag & BLUE_TONE)
        printf("Blue tone is enabled with parameter %hd\n", parameters[2]);
    // Add more conditions as needed...
}
