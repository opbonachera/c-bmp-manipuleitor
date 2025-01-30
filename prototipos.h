#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTPYES_H_INCLUDED

typedef void(*ModifyPixel) (t_pixel* pixel, float intensity);
typedef void(*ModifyMatrix)(t_pixel** originalMat, t_pixel** newMat, int rows, int cols);
typedef void(*ConcatMatrix)(t_pixel** firstOgMat, t_pixel** secondOgMat, t_pixel** newMat, t_header* firstOgHeader, t_header* secondOgHeader, t_header* newHeader);
typedef void(*ShrinkMatrix)(t_pixel** originalMat, t_pixel** newMat, int newHeight, int newWidth, t_header* header);

#endif // PROTOTYPES_H_INCLUDED
