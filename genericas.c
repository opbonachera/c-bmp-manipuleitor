#include "genericas.h"
#include "estructuras.h"
#include "constantes.h"

int modifyImageTone(FILE* originalImage, char* newFilename, int parameter, ModifyPixel applyFilter)
{
    FILE* newImage = fopen(newFilename, "wb");

    if (!newImage)
    {
        printf("\nError creating image (%s)\n.", newFilename);
        return ERROR_OPENING_FILE;
    }

    t_header header;

    readHeader(originalImage, &header);
    writeHeader(originalImage, newImage, &header);

    t_pixel** originalMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), header.alto, header.ancho);
    t_pixel** newMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), header.alto, header.ancho);

    cargarMatriz(originalImage, originalMatrix, header.alto, header.ancho);

    for (int i = 0; i < header.alto; i++)
    {
        for (int j = 0; j < header.ancho; j++)
        {
            newMatrix[i][j] = originalMatrix[i][j];
            applyFilter(&newMatrix[i][j], (float)parameter);
        }
    }

    escribirArchivo(newImage, newMatrix, header.alto, header.ancho);

    matrizDestruir((void**)originalMatrix, header.alto);
    matrizDestruir((void**)newMatrix, header.alto);
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

    cargarMatriz(originalImage, originalMatrix, originalHeader.alto, originalHeader.ancho);

    modifyMatrix(originalMatrix, rotatedMatrix, originalHeader.alto, originalHeader.ancho);

    escribirArchivo(newImage, rotatedMatrix, originalHeader.ancho, originalHeader.alto);

    matrizDestruir((void**)originalMatrix, originalHeader.alto);
    matrizDestruir((void**)rotatedMatrix, originalHeader.ancho);

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

    cargarMatriz(originalImage, originalMatrix, originalHeader.alto, originalHeader.ancho);

    modifyMatrix(originalMatrix, mirroredMatrix, originalHeader.alto, originalHeader.ancho);

    escribirArchivo(newImage, mirroredMatrix, originalHeader.alto, originalHeader.ancho);

    matrizDestruir((void**)originalMatrix, originalHeader.alto);
    matrizDestruir((void**)mirroredMatrix, originalHeader.alto);

    fclose(newImage);

    return OK;
}

int cropImage(FILE* originalImage, char* newFilename, int parameter, ModifyMatrix modifyMatrix)
{
    FILE* newImage;
    int newWidth, newHeight;
    t_header originalHeader;

    newImage = fopen(newFilename, "wb");
    if (!newImage)
        return ERROR_OPENING_FILE;

    readHeader(originalImage, &originalHeader);

    newWidth = originalHeader.ancho * parameter / 100;
    newHeight = originalHeader.alto * parameter / 100;

    originalHeader.ancho = newWidth;
    originalHeader.alto = newHeight;

    writeHeader(originalImage, newImage, &originalHeader);

    t_pixel** originalMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), originalHeader.alto * 100 / parameter, originalHeader.ancho * 100 / parameter);
    t_pixel** croppedMatrix = (t_pixel**)initMatrix(sizeof(t_pixel), newHeight, newWidth);

    cargarMatriz(originalImage, originalMatrix, originalHeader.alto * 100 / parameter, originalHeader.ancho * 100 / parameter);

    modifyMatrix(originalMatrix, croppedMatrix, newHeight, newWidth);

    escribirArchivo(newImage, croppedMatrix, newHeight, newWidth);

    matrizDestruir((void**)originalMatrix, originalHeader.alto * 100 / parameter);
    matrizDestruir((void**)croppedMatrix, newHeight);

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
    cargarMatriz(originalImage, originalMatrix, originalHeader.alto, originalHeader.ancho);

    shrink(originalMatrix, shrunkMatrix, newHeight, newWidth, &originalHeader);

    escribirArchivo(newImage, shrunkMatrix, newHeight, newWidth);
    modificarDimensiones(newImage, newWidth, newHeight);

    matrizDestruir((void**)originalMatrix, originalHeader.alto);
    matrizDestruir((void**)shrunkMatrix, newHeight);

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
    cargarMatriz(firstImage, matrixFirst, header1.alto, header1.ancho);
    cargarMatriz(secondImage, matrixSecond, header2.alto, header2.ancho);

    concat(matrixFirst, matrixSecond, concatenatedMatrix, &header1, &header2, &newHeader);

    fseek(newImage, header1.comienzoImagen, SEEK_SET);
    escribirArchivo(newImage, concatenatedMatrix, newHeight, newWidth);

    modificarDimensiones(newImage, newWidth, newHeight);

    matrizDestruir((void**)matrixFirst, header1.alto);
    matrizDestruir((void**)matrixSecond, header2.alto);
    matrizDestruir((void**)concatenatedMatrix, newHeight);

    fclose(newImage);

    return OK;
}

void genGrayscale       (t_pixel* pixel, float  intensity);
void genNegative        (t_pixel* pixel, float  intensity);
void genRaiseContrast   (t_pixel* pixel, float  intensity);
void genReduceContrast  (t_pixel* pixel, float  intensity);
void genChangeRedTone   (t_pixel* pixel, float  intensity);
void genChangeGreenTone (t_pixel* pixel, float  intensity);
void genChangeBlueTone  (t_pixel* pixel, float  intensity);
void genRotateImageLeft         (t_pixel** originalMat, t_pixel** newMat, int rows, int cols);
void genRotateImageRight        (t_pixel** originalMat, t_pixel** newMat, int rows, int cols);
void genMirrorImageVertically   (t_pixel** originalMat, t_pixel** newMat, int rows, int cols);
void genMirrorImageHorizontally (t_pixel** originalMat, t_pixel** newMat, int rows, int cols);
void genPixelImage              (t_pixel** originalMat, t_pixel** newMat, int rows, int cols);
void genCropImage               (t_pixel** originalMat, t_pixel** newMat, int rows, int cols);
void genConcatImageVertically  (t_pixel** firstOgMat, t_pixel** secondOgMat, t_pixel** newMat, t_header* firstOgHeader, t_header* secondOgHeader, t_header* newHeader);
void genConcatImageHorizontally(t_pixel** firstOgMat, t_pixel** secondOgMat, t_pixel** newMat, t_header* firstOgHeader, t_header* secondOgHeader, t_header* newHeader);
void genShrinkImage(t_pixel** originalMat, t_pixel** newMat, int newHeight, int newWidth, t_header* header);
