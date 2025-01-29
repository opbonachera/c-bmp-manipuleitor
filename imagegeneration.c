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

    printf("Config file from bmpmanipuleitor (%s)\n", configFile);

    processFilterFile(configFile, 0, parameters, flag);

    generateImages(flag, parameters);

    return OK;
}

void generateImages(short int flag, short int parameters[])
{
    for(int i=0; i<3; i++)
        printf("Parameter: [%d]\n", parameters[i]);

    if (flag & RED_TONE)
        printf("Red tone is enabled with parameter %hd\n", parameters[0]);
    if (flag & BLUE_TONE)
        printf("Blue tone is enabled with parameter %hd\n", parameters[1]);

}
