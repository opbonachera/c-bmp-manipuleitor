#include "genericas.h"
#include "constantes.h"

// ----- FUNCIONES GENERICAS -----
void genChangeRedTone(t_pixel* pixel, float intensidad)
{
    float multiplicador = 1 + (intensidad / 100);
    pixel->pixel[2] = (pixel->pixel[2] * multiplicador) > 255 ? 255 : (unsigned char)(pixel->pixel[2] * multiplicador);
}

void genChangeGreenTone(t_pixel* pixel, float intensidad)
{
    float multiplicador = 1 + (intensidad / 100);
    pixel->pixel[1] = (pixel->pixel[1] * multiplicador) > 255 ? 255 : (unsigned char)(pixel->pixel[1] * multiplicador);
}

void genChangeBlueTone(t_pixel* pixel, float intensidad)
{
    float multiplicador = 1 + (intensidad / 100);
    pixel->pixel[0] = (pixel->pixel[0] * multiplicador) > 255 ? 255 : (unsigned char)(pixel->pixel[0] * multiplicador);
}

void genRaiseContrast(t_pixel* pixel, float intensidad)
{
    float porcentaje= 1 + (intensidad/100);

    for(int i=0; i<3; i++)
    {
        pixel->pixel[i] = (pixel->pixel[i] * porcentaje) > 255 ? 255 : (unsigned char)(pixel->pixel[i] * porcentaje);
    }
}

void genReduceContrast(t_pixel* pixel, float intensidad)
{
    float porcentaje = 1 - (intensidad/100);

    for(int i=0; i<3; i++)
    {
        pixel->pixel[i] = (pixel->pixel[i] * porcentaje) > 255 ? 255 : (unsigned char)(pixel->pixel[i] * porcentaje);
    }
}

void genNegative(t_pixel* pixel, float intensidad)
{
    for(int i=0; i<3; i++)
    {
        pixel->pixel[i] = ~pixel->pixel[i];
    }

}

void genGrayscale(t_pixel* pixel, float intensidad)
{
    unsigned char promedio = (pixel->pixel[0] + pixel->pixel[1] + pixel->pixel[2]) / 3;
    pixel->pixel[0] = pixel->pixel[1] = pixel->pixel[2] = promedio;
}

void genRotateImageRight(t_pixel** imagenOriginal, t_pixel** imagenNueva, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            imagenNueva[columnas - j - 1][i] = imagenOriginal[i][j];
        }
    }
}

void genRotateImageLeft(t_pixel** matImagen, t_pixel** matImagenNueva, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            matImagenNueva[j][filas - i - 1] = matImagen[i][j];
        }
    }
}

void genMirrorImageHorizontally(t_pixel** matImagen, t_pixel** matImagenNueva, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matImagenNueva[i][j] = matImagen[i][columnas - 1 - j];
        }
    }
}

void genMirrorImageVertically(t_pixel** matImagen, t_pixel** matImagenNueva, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matImagenNueva[i][j] = matImagen[filas - 1 - i][j];
        }
    }
}

void genPixelImage(t_pixel** matImagen, t_pixel** matImagenNueva, int filas, int columnas)
{
    int n=4;
    for(int i=0; i<filas; i+=n)
    {
        for(int j=0; j<columnas; j+=n)
        {
            unsigned int sumaRojo=0, sumaVerde=0, sumaAzul=0;

            for(int k=0; k<n; k++)
            {
                for(int l=0; l<n; l++)
                {
                    sumaRojo  += matImagen[k+i][l+j].pixel[0];
                    sumaVerde += matImagen[k+i][l+j].pixel[1];
                    sumaAzul  += matImagen[k+i][l+j].pixel[2];
                }
            }

            unsigned char prmRojo =  MIN(sumaRojo / (n * n), 255);
            unsigned char prmVerde = MIN(sumaVerde / (n * n), 255);
            unsigned char prmAzul =  MIN(sumaAzul / (n * n), 255);


            for(int k=0; k<n; k++)
            {
                for(int l=0; l<n; l++)
                {
                    matImagenNueva[k+i][l+j].pixel[0] = prmRojo;
                    matImagenNueva[k+i][l+j].pixel[1] = prmVerde;
                    matImagenNueva[k+i][l+j].pixel[2] = prmAzul;
                }
            }
        }
    }
}

void genCropImage(t_pixel** matImagen, t_pixel** matImagenNueva, int filas, int columnas)
{
    for (int y = 0; y < filas; y++)
    {
        for (int x = 0; x < columnas; x++)
        {
            matImagenNueva[y][x] = matImagen[y][x];
        }
    }
}

void genConcatImageHorizontally(t_pixel** matImagen1, t_pixel** matImagen2, t_pixel** matImagenNueva, t_header* cabecera1, t_header* cabecera2, t_header* cabeceraNueva)
{
    // rellenarMatrizDeRojo(cabeceraNueva->alto,cabeceraNueva->ancho, matImagenNueva);

    for (int i = 0; i < ((int)cabecera1->alto); i++)
    {
        for (int j = 0; j < ((int)cabecera1->ancho); j++)
        {
            matImagenNueva[i][j] = matImagen1[i][j];
        }
    }

    for(int i=0; i<cabecera2->alto; i++)
    {
        for(int j=0; j<cabecera2->ancho; j++)
        {
            matImagenNueva[i][j + cabecera1->ancho] = matImagen2[i][j];
        }
    }

}

void genConcatImageVertically(t_pixel** matImagen1, t_pixel** matImagen2, t_pixel** matImagenNueva, t_header* cabecera1, t_header* cabecera2, t_header* cabeceraNueva)
{
    // rellenarMatrizDeRojo(cabeceraNueva->alto,cabeceraNueva->ancho, matImagenNueva);

    for (int i = 0; i < ((int)cabecera1->alto); i++)
    {
        for (int j = 0; j < ((int)cabecera1->ancho); j++)
        {
            matImagenNueva[i][j] = matImagen1[i][j];
        }
    }

    for(int i=0; i<cabecera2->alto; i++)
    {
        for(int j=0; j<cabecera2->ancho; j++)
        {
            matImagenNueva[i + cabecera1->alto][j] = matImagen2[i][j];
        }
    }

}

void genShrinkImage(t_pixel** matImagen, t_pixel** matImagenNueva, int nuevoAlto, int nuevoAncho, t_header* cabecera)
{
    float alRatio = (float)cabecera->alto / nuevoAlto;
    float anRatio = (float)cabecera->ancho / nuevoAncho;

    for (int i = 0; i < nuevoAlto; i++) {
        for (int j = 0; j < nuevoAncho; j++) {

            int nI = (int)(i * alRatio);
            int nJ = (int)(j * anRatio);

            matImagenNueva[i][j] = matImagen[nI][nJ];
        }
    }
}
