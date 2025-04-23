#ifndef GENERICAS_H_INCLUDED
#define GENERICAS_H_INCLUDED

#include <stdio.h>

#include "estructuras.h"
#include "prototipos.h"

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

#endif // UTILITIES_H_INCLUDED
