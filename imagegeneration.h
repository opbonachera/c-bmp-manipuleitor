#ifndef IMAGE_GENERATION_H_INCLUDED
#define IMAGE_GENERATION_H_INCLUDED

#include <stddef.h>
#include <stdio.h>

#include "constantes.h"
#include "estructuras.h"
#include "genericas.h"

int  bmpManipuleitor(int argc, char* argv[]);
int  readHeader(FILE* img, t_header* header);
void modificarDimensiones(FILE* img, int nuevoX, int nuevoY);
void generateImages(short int* flag, short int parameters[], FILE* firstImage, FILE* secondImage, char* filename);
void writeHeader(FILE* img, FILE* nueva, t_header* header);

int modifyImageTone(FILE* ogImage, char* newFilename, int parametro, ModifyPixel aplicarFiltro);
int rotateImage    (FILE* ogImage, char* newFilename, ModifyMatrix modificarMatriz);
int mirrorImage    (FILE* ogImage, char* newFilename, ModifyMatrix modificarMatriz);
int cropImage      (FILE* ogImage, char* newFilename, int parametro, ModifyMatrix modificarMatriz);
int shrinkImage    (FILE* ogImage, char* newFilename, int parametro, ShrinkMatrix achicar);
int concatImages   (FILE* firstOgImage, FILE* img2, char* newFilename, ConcatMatrix concat, char m);


#endif // IMAGE_GENERATION_H_INCLUDED
