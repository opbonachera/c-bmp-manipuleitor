#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define RED_TONE            1 << 1
#define BLUE_TONE           1 << 2
#define GREEN_TONE          1 << 3
#define REDUCE_CONTRAST     1 << 4
#define INCREASE_CONTRAST   1 << 5
#define GRAYSCALE           1 << 6
#define NEGATIVE            1 << 7
#define CROP                1 << 8
#define SHRINK              1 << 9
#define ROTATE_LEFT         1 << 10
#define ROTATE_RIGHT        1 << 11
#define FLIP_VERTICAL       1 << 12
#define FLIP_HORIZONTAL     1 << 13
#define CONCAT_VERTICAL     1 << 14
#define CONCAT_HORIZONTAL   1 << 15
#define PIXELATE            1 << 16
#define BLUR                1 << 17

#define OK                      0b0
#define ERROR_OPENING_FILE      0b10
#define ERROR_ALLOCATING_MEMORY 0b11

#endif // UTILITIES_H_INCLUDED
