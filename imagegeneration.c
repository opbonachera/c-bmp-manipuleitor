#include "imagegeneration.h"


int bmpManipuleitor(int argc, char* argv[])
{
    char* imageFiles[2] = {NULL, NULL};
    char* configFile = NULL;

    short int parameters[8] = {0};
    int flag = 0;

    if (argc < 2)
    {
        printf("Insufficient arguments. Usage: bmpManipuleitor <args>\n");
        return -1;
    }

    processCommandLine(argc, argv, parameters, imageFiles, &configFile, &flag);

    processFilterFile(configFile, 0, parameters, &flag);

    FILE* firstImage = fopen(imageFiles[0], "rb");
    if(!firstImage)
    {
        printf("Unable to open first file: (%s)\n", imageFiles[0]);
    }

    FILE* secondImage = NULL;

    if(imageFiles[1] == NULL)
    {
        printf("No second file has been provided.\n");
    }else
    {
        FILE* secondImage = fopen(imageFiles[1], "rb");
        if(!secondImage)
        {
            printf("Unable to open second file: (%s)\n", imageFiles[1]);
            fclose(firstImage);
        }
    }


    generateImages(&flag, parameters, firstImage, secondImage, imageFiles[0]);

    return OK;
}

void generateImages(int* flag, short int parameters[], FILE* firstImage, FILE* secondImage, char* filename)
{
    char* newImageName;

    if (*flag & RED_TONE)
    {
        newImageName = generateImageName("red-tone", filename);
        if (newImageName)
        {
            modifyImageTone(firstImage, newImageName, parameters[0], genChangeRedTone);
            free(newImageName);
        }
    }

    if (*flag & BLUE_TONE)
    {
        newImageName = generateImageName("blue-tone", filename);
        if (newImageName)
        {
            modifyImageTone(firstImage, newImageName, parameters[0], genChangeBlueTone);
            free(newImageName);
        }
    }

    if (*flag & GREEN_TONE)
    {
        newImageName = generateImageName("green-tone", filename);
        if (newImageName)
        {
            modifyImageTone(firstImage, newImageName, parameters[0], genChangeGreenTone);
            free(newImageName);
        }
    }

    if (*flag & INCREASE_CONTRAST)
    {
        newImageName = generateImageName("high-contrast", filename);
        if (newImageName)
        {
            modifyImageTone(firstImage, newImageName, parameters[0], genRaiseContrast);
            free(newImageName);
        }
    }

    if (*flag & REDUCE_CONTRAST)
    {
        newImageName = generateImageName("low-contrast", filename);
        if (newImageName)
        {
            modifyImageTone(firstImage, newImageName, parameters[0], genReduceContrast);
            free(newImageName);
        }
    }

    if (*flag & CROP)
    {
        newImageName = generateImageName("cropped", filename);
        if (newImageName)
        {
            cropImage(firstImage, newImageName, 90, genCropImage);
            free(newImageName);
        }
    }


    if (*flag & SHRINK)
        printf("Shrink is enabled with parameter %hd\n", parameters[6]);

    if (*flag & GRAYSCALE)
    {
        newImageName = generateImageName("grayscale", filename);
        if (newImageName)
        {
            modifyImageTone(firstImage, newImageName, parameters[0], genGrayscale);
            free(newImageName);
        }
    }

    if (*flag & NEGATIVE)
    {
        newImageName = generateImageName("negative", filename);
        if (newImageName)
        {
            modifyImageTone(firstImage, newImageName, parameters[0], genNegative);
            free(newImageName);
        }
    }

    if (*flag & ROTATE_LEFT)
    {

    }
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

    return;
}

void modificarDimensiones(FILE* image, int nuevoX, int nuevoY)
{
    fseek(image, 18, SEEK_SET);
    fwrite(&nuevoX, sizeof(unsigned int), 1, image);
    fwrite(&nuevoY, sizeof(unsigned int), 1, image);
}

int readHeader(FILE* image, t_header *cabecera)
{
    printf("reading header");
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


int modifyImageTone(FILE* originalImage, char* newFilename, int parameter, ModifyPixel applyFilter)
{
    printf("New file created (%s)\n", newFilename);
    FILE* newImage = fopen(newFilename, "wb");

    if (!newImage)
    {
        printf("\nError creating image (%s)\n.", newFilename);
        return ERROR_OPENING_FILE;
    }

    t_header header;

    readHeader(originalImage, &header);
    printf("Image dimensions: %u x %u, Bit depth: %hu\n", header.ancho, header.alto, header.profundidad);
    writeHeader(originalImage, newImage, &header);

    t_pixel** originalMatrix = (t_pixel**)initMatrix(header.alto, header.ancho, sizeof(t_pixel));
    t_pixel** newMatrix = (t_pixel**)initMatrix(header.alto, header.ancho, sizeof(t_pixel));


    matrixFromFile(header.alto, header.ancho, originalImage, originalMatrix);

    for (int i = 0; i < header.alto; i++)
    {
        for (int j = 0; j < header.ancho; j++)
        {
            newMatrix[i][j] = originalMatrix[i][j];
            applyFilter(&newMatrix[i][j], (float)parameter);
        }
    }

    writeFile(newImage, newMatrix, header.alto, header.ancho);

    destroyMatrix((void**)originalMatrix, header.alto);
    destroyMatrix((void**)newMatrix, header.alto);

    fclose(newImage);

    return OK;
}

int rotateImage(FILE* originalImage, char* newFilename, ModifyMatrix modifyMatrix)
{
    FILE* newImage = fopen(newFilename, "wb");

    if (!newImage)
        return ERROR_OPENING_FILE;

    if (!originalImage)
        return ERROR_OPENING_FILE;

    t_header originalHeader;

    readHeader(originalImage, &originalHeader);
    writeHeader(originalImage, newImage, &originalHeader);

    t_pixel** originalMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), originalHeader.alto, originalHeader.ancho);
    t_pixel** rotatedMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), originalHeader.ancho, originalHeader.alto);

    matrixFromFile(originalHeader.alto, originalHeader.ancho, originalImage, originalMatrix);

    modifyMatrix(originalMatrix, rotatedMatrix, originalHeader.alto, originalHeader.ancho);

    writeFile(newImage, rotatedMatrix, originalHeader.ancho, originalHeader.alto);

    destroyMatrix((void**)originalMatrix, originalHeader.alto);
    destroyMatrix((void**)rotatedMatrix, originalHeader.ancho);

    modificarDimensiones(newImage, originalHeader.alto, originalHeader.ancho);

    fclose(newImage);

    return OK;
}

int mirrorImage(FILE* originalImage, char* newFilename, ModifyMatrix modifyMatrix)
{
    FILE* newImage = fopen(newFilename, "wb");

    if (!newImage)
        return ERROR_OPENING_FILE;

    if (!originalImage)
        return ERROR_OPENING_FILE;

    t_header originalHeader;

    readHeader(originalImage, &originalHeader);
    writeHeader(originalImage, newImage, &originalHeader);

    t_pixel** originalMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), originalHeader.alto, originalHeader.ancho);
    t_pixel** mirroredMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), originalHeader.alto, originalHeader.ancho);

    matrixFromFile(originalHeader.alto, originalHeader.ancho, originalImage, originalMatrix);

    modifyMatrix(originalMatrix, mirroredMatrix, originalHeader.alto, originalHeader.ancho);

    writeFile(newImage, mirroredMatrix, originalHeader.alto, originalHeader.ancho);

    destroyMatrix((void**)originalMatrix, originalHeader.alto);
    destroyMatrix((void**)mirroredMatrix, originalHeader.alto);

    fclose(newImage);

    return OK;
}

int cropImage(FILE* originalImage, char* newFilename, int parameter, ModifyMatrix modifyMatrix)
{
    FILE* newImage;
    t_header originalHeader;

    newImage = fopen(newFilename, "wb");
    if (!newImage)
        return ERROR_OPENING_FILE;

    readHeader(originalImage, &originalHeader);

    int originalWidth = originalHeader.ancho;
    int originalHeight = originalHeader.alto;

    int newWidth = originalWidth * parameter / 100;
    int newHeight = originalHeight * parameter / 100;

    t_pixel** originalMatrix = (t_pixel**)initMatrix(originalHeight, originalWidth, sizeof(t_pixel));
    t_pixel** croppedMatrix = (t_pixel**)initMatrix(newHeight, newWidth, sizeof(t_pixel));

    matrixFromFile(originalHeight, originalWidth, originalImage, originalMatrix);

    modifyMatrix(originalMatrix, croppedMatrix, newHeight, newWidth);


    originalHeader.ancho = newWidth;
    originalHeader.alto = newHeight;

    writeHeader(originalImage, newImage, &originalHeader);
    writeFile(newImage, croppedMatrix, newHeight, newWidth);

    destroyMatrix((void**)originalMatrix, originalHeight);
    destroyMatrix((void**)croppedMatrix, newHeight);

    modificarDimensiones(newImage, newWidth, newHeight);

    fclose(newImage);
    return OK;
}


int shrinkImage(FILE* originalImage, char* newFilename, int parameter, ShrinkMatrix shrink)
{
    FILE* newImage;
    t_header originalHeader;

    newImage = fopen(newFilename, "wb");
    if (!newImage)
        return ERROR_OPENING_FILE;

    readHeader(originalImage, &originalHeader);
    writeHeader(originalImage, newImage, &originalHeader);

    int newHeight = originalHeader.alto * parameter / 100;
    int newWidth = originalHeader.ancho * parameter / 100;

    t_pixel** originalMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), originalHeader.alto, originalHeader.ancho);
    t_pixel** shrunkMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), newHeight, newWidth);

    fseek(originalImage, originalHeader.comienzoImagen, SEEK_SET);

    matrixFromFile(originalHeader.alto, originalHeader.ancho, originalImage, originalMatrix);

    shrink(originalMatrix, shrunkMatrix, newHeight, newWidth, &originalHeader);

    writeFile(newImage, shrunkMatrix, newHeight, newWidth);
    modificarDimensiones(newImage, newWidth, newHeight);

    destroyMatrix((void**)originalMatrix, originalHeader.alto);
    destroyMatrix((void**)shrunkMatrix, newHeight);

    fclose(newImage);

    return OK;
}

int concatImages(FILE* firstImage, FILE* secondImage, char* newFilename, ConcatMatrix concat, char mode)
{
    if (!firstImage || !secondImage)
    {
        printf("ERROR_OPENING_FILE: para concatenar imágenes deben enviarse dos archivos .bmp \n");
        return ERROR_INSUFFICIENT_FILES;
    }

    FILE* newImage = fopen(newFilename, "wb");

    if (!newImage)
        return ERROR_OPENING_FILE;

    t_header header1, header2, newHeader;
    readHeader(firstImage, &header1);
    readHeader(secondImage, &header2);
    readHeader(secondImage, &newHeader);

    int newHeight, newWidth;
    if (mode == 'V')
    {
        newHeight = header1.alto + header2.alto;
        newWidth = (header1.ancho > header2.ancho) ? header1.ancho : header2.ancho;
    }
    else
    {
        newHeight = (header1.alto > header2.alto) ? header1.alto : header2.alto;
        newWidth = header1.ancho + header2.ancho;
    }

    newHeader.alto = newHeight;
    newHeader.ancho = newWidth;

    writeHeader(firstImage, newImage, &newHeader);

    t_pixel** matrixFirst = (t_pixel**)initMatrix(sizeof(t_pixel), header1.alto, header1.ancho);
    t_pixel** matrixSecond = (t_pixel**)initMatrix(sizeof(t_pixel), header2.alto, header2.ancho);
    t_pixel** concatenatedMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), newHeight, newWidth);

    fseek(secondImage, header2.comienzoImagen, SEEK_SET);
    fseek(firstImage, header1.comienzoImagen, SEEK_SET);

    matrixFromFile(header1.alto, header1.ancho, firstImage, matrixFirst);
    matrixFromFile(header1.alto, header1.ancho, secondImage, matrixSecond);

    concat(matrixFirst, matrixSecond, concatenatedMatrix, &header1, &header2, &newHeader);

    fseek(newImage, header1.comienzoImagen, SEEK_SET);
    writeFile(newImage, concatenatedMatrix, newHeight, newWidth);

    modificarDimensiones(newImage, newWidth, newHeight);

    destroyMatrix((void**)matrixFirst, header1.alto);
    destroyMatrix((void**)matrixSecond, header2.alto);
    destroyMatrix((void**)concatenatedMatrix, newHeight);

    fclose(newImage);

    return OK;
}
