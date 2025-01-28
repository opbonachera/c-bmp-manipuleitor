#include "imagegeneration.h"
#include "commandLine.h"

int bmpManipuleitor(int argc, char* argv[])
{
    char* imageFiles[2] = {NULL, NULL};
    char* configFile = NULL;

    short int parameters[8] = {0};
    int flag = 0;

    if (argc < 2) {
        printf("Insufficient arguments. Usage: bmpManipuleitor <args>\n");
        return -1;
    }

    processCommandLine(argc, argv, parameters, imageFiles, &configFile, &flag);

    printf("Flag is (%d)", flag);

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
