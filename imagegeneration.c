#include "imagegeneration.h"
#include "commandLine.h"

int bmpManipuleitor(int argc, char* argv[])
{
    char* imageFiles[2] = {NULL, NULL};
    char* configFile = NULL;

    short int parameters[8] = {0};
    short int flag = 0;

    if (argc < 2) {
        printf("Insufficient arguments. Usage: bmpManipuleitor <args>\n");
        return -1;
    }

    processCommandLine(argc, argv, parameters, imageFiles, &configFile, &flag);

    processFilterFile(configFile, 0, parameters, &flag);

    generateImages(&flag, parameters);

    return OK;
}

void generateImages(short int* flag, short int parameters[])
{
    // for(int i=0; i<8; i++)
    //     printf("[%d]\n", parameters[i]);
    if (*flag & RED_TONE)
        printf("Red tone is enabled with parameter %hd\n", parameters[0]);
    if (*flag & BLUE_TONE)
        printf("Blue tone is enabled with parameter %hd\n", parameters[1]);
    if (*flag & GREEN_TONE)
        printf("Green tone is enabled with parameter %hd\n", parameters[2]);
    if (*flag & REDUCE_CONTRAST)
        printf("Reduce contrast is enabled with parameter %hd\n", parameters[3]);
    if (*flag & INCREASE_CONTRAST)
        printf("Increase contrast is enabled with parameter %hd\n", parameters[4]);
    if (*flag & CROP)
        printf("Crop is enabled with parameter %hd\n", parameters[5]);
    if (*flag & SHRINK)
        printf("Shrink is enabled with parameter %hd\n", parameters[6]);

    if (*flag & GRAYSCALE)
        printf("Grayscale is enabled\n");
    if (*flag & NEGATIVE)
        printf("Negative is enabled\n");
    if (*flag & ROTATE_LEFT)
        printf("Rotate left is enabled\n");
    if (*flag & ROTATE_RIGHT)
        printf("Rotate right is enabled\n");
    if (*flag & FLIP_VERTICAL)
        printf("Flip vertical is enabled\n");
    if (*flag & FLIP_HORIZONTAL)
        printf("Flip horizontal is enabled\n");
    if (*flag & CONCAT_VERTICAL)
        printf("Concat vertical is enabled\n");
    if (*flag & CONCAT_HORIZONTAL)
        printf("Concat horizontal is enabled\n");
    if (*flag & PIXELATE)
        printf("Pixelate is enabled\n");
    if (*flag & BLUR)
        printf("Blur is enabled\n");
}

void modificarDimensiones(FILE* image, int nuevoX, int nuevoY)
{
    fseek(image, 18, SEEK_SET);
    fwrite(&nuevoX, sizeof(unsigned int), 1, image);
    fwrite(&nuevoY, sizeof(unsigned int), 1, image);
}

int readHeader(FILE* image, t_header *cabecera)
{
    fseek(image, 2, SEEK_SET);
    fread(&cabecera->tamArchivo, sizeof(unsigned int), 1, image);

    fseek(image, 14, SEEK_SET);
    fread(&cabecera->tamEncabezado, sizeof(unsigned int), 1, image);

    fseek(image, 10, SEEK_SET);
    fread(&cabecera->comienzoImagen, sizeof(unsigned int), 1, image);

    fseek(image, 18, SEEK_SET);
    fread(&cabecera->ancho, sizeof(unsigned int), 1, image);

    fseek(image, 22, SEEK_SET);
    fread(&cabecera->alto, sizeof(unsigned int), 1, image);

    fseek(image, 28, SEEK_SET);
    fread(&cabecera->profundidad, sizeof(unsigned short), 1, image);

    fseek(image, 0, SEEK_SET);
    return 0;
}

void writeHeader(FILE* image, FILE* newImage, t_header* ogHeader)
{
    char bytes[ogHeader->comienzoImagen];

    fread(&bytes, sizeof(bytes), 1, image);
    fwrite(&bytes, sizeof(bytes), 1, newImage);
}
