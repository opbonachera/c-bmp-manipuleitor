/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Bonachera
    Nombre: Ornella
    DNI: 46119546
    Entrega: Si
    -----------------
    Apellido: Pityla
    Nombre: Damian
    DNI: 45754471
    Entrega: Si
    -----------------
    (Sólo para grupos de tres integrantes)
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

*/
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> // Para time()

#include "constantes.h"
#include "estructuras.h"
#include "funciones_estudiante.h"


int solucion(int argc, char* argv[])
{
/*
    Aquí deben hacer el código que solucione lo solicitado.
    Todas las funciones utilizadas deben estar declaradas en este archivo, y en su respectivo .h
*/
    crearImagen(argc, argv);

    return TODO_OK;
}

int crearImagen(int argc, char *argv[])
{
    // Crea la nueva imagen en formato BMP de 24 bits.
    t_metadata metadataNuevo, metadataOriginal;

    char nombreImgOriginal[256], nombreImgNueva[256];
    int pos, argCod;

    pos = posicionBmp(argc, argv);

    if(pos==-1)
    {
        printf("No se puede ingresar mas de un archivo BMP. Para saber como utilizar el programa, ingrese --help.");
        return 1;
    }else if(pos==0)
    {
        printf("No se encontro ningun archivo BMP");
        return ARCHIVO_NO_ENCONTRADO;
    }

    nombreImgOriginal[0] = '\0';
    strcpy(nombreImgOriginal, argv[pos]);

    for(int i=1; i<argc; i++)
    {
        if(i!=pos){
            argCod = validarDevolverCodigo(argv[i]);
        if(argCod==-1)
            printf("Funcionalidad: %d no existente. Para ver las funcionalidades disponibles, ingrese --help.", i);
        else
        {
            eliminarPrimerosDosCaracteres(argv[i]);
            nombreImgNueva[0] = '\0';
            strcat(nombreImgNueva,"estudiante_");
            strcat(nombreImgNueva,argv[i]);
            strcat(nombreImgNueva,".bmp");

            FILE *pImagenNueva = fopen(nombreImgNueva, "wb");

            if(pImagenNueva== NULL) {
                printf("Ocurrió un error al abrir el archivo de salida. Intente nevamente.");
                return -3;
            }

            leerMetadata(nombreImgOriginal, &metadataOriginal);

            // Guardamos la metadata de la imagen original solo por si debemos hacerle modificaciones
            escribirMetadata(pImagenNueva, nombreImgOriginal, metadataOriginal.comienzoImagen);
            // Escribimos la metadata en la imagen nueva
            escribirDatos(pImagenNueva, nombreImgOriginal, argCod, metadataOriginal.comienzoImagen, &metadataNuevo, &metadataOriginal);
            // Escribimos los pixeles de la imagen original en la nueva
            leerMetadata(nombreImgNueva, &metadataNuevo);
            // Leemos la cebcera de la imagen nueva

            fclose(pImagenNueva);
        }
      }
    }
    return TODO_OK;
}

int posicionBmp(const int argc, char *argv[])
{
    int cant=0, encontrado=0;
    char *extension;
    for (int i = 1; i < argc; i++) {

        extension = strrchr(argv[i], '.');

        if (extension != NULL && strcmp(extension, ".bmp") == 0) {
            encontrado = i;
            cant++;
        }
    }

    if(cant > 1) encontrado =-1;
    return encontrado;
}

int validarDevolverCodigo(char arg[]){
    // Opciones de modificar contraste (Calcula min y max)
    if(!strcmpi(arg, "--aumentar-contraste"))return 1;
    if(!strcmpi(arg, "--reducir-contraste")) return 2;
    // -----------
    if(!strcmpi(arg, "--negativo")) return 3;
    if(!strcmpi(arg, "--escala-de-grises")) return 4;
    if(!strcmpi(arg, "--tonalidad-azul")) return 5;
    if(!strcmpi(arg, "--tonalidad-verde")) return 6;
    if(!strcmpi(arg, "--tonalidad-roja")) return 7;
    if(!strcmpi(arg, "--comodin")) return 9;
    // Opciones de modificar dimensiones
    if(!strcmpi(arg, "--rotar-derecha")) return 10;
    if(!strcmpi(arg, "--rotar-izquierda")) return 11;
    if(!strcmpi(arg, "--recortar")) return 12;

    return -1;
}


int aplicarFiltro(t_pixel* px, int codFiltro, int min_value, int max_value)
{
    switch(codFiltro)
    {
        case 1:
            aumentarContraste(px, min_value, max_value);
            break;
        case 2:
            reducirContraste(px, min_value, max_value);
            break;
        case 3:
            invertirColores(px);
            break;
        case 4:
            escalaDeGrises(px);
            break;
        case 5:
            aumentarColor(px, 0);
            break;
        case 6:
            aumentarColor(px,1);
            break;
        case 7:
            aumentarColor(px,2);
            break;
        case 9:
            aumentarColorAleatorio(px);
        default:
            return 1;
    }
    return TODO_OK;
}

void eliminarPrimerosDosCaracteres(char *cadena) {
    size_t longitud = strlen(cadena);

    // Desplaza la cadena dos caracteres hacia la izquierda
    for (size_t i = 2; i <= longitud; i++) {
        cadena[i - 2] = cadena[i];
    }
}

int escribirMetadata(FILE *archivoNuevo, char nombreImgOriginal[], unsigned int comienzoImagen)
{
    // Copia TODOS los datos de la metadata del archivo original al nuevo
    FILE *archivoOriginal;

    archivoOriginal = fopen(nombreImgOriginal,"rb");

    if (archivoOriginal == NULL || archivoNuevo == NULL) {
        perror("Error opening file");
        return 1;
    }

    unsigned char byte[3];

    for(int i=0; i<comienzoImagen;i++){
        fread(&byte, sizeof(unsigned char), 1, archivoOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, archivoNuevo);
    }

    fclose(archivoOriginal);

    return TODO_OK;
}

int escribirDatos(FILE *archivoNuevo, char nombreImgOriginal[], int argCod, unsigned int comienzoImagen, t_metadata *metadata_entrada, t_metadata *metadata_salida)
{
    // Escribe los pixeles que componen la imagen
    FILE *archivoOriginal;

    t_pixel px;

    unsigned char min_value = 255;
    unsigned char max_value = 0;

    archivoOriginal = fopen(nombreImgOriginal,"rb");

    if (archivoOriginal == NULL || archivoNuevo == NULL) {
        perror("Ocurrio un error. Intente nuevamente.\n");
        return 1;
    }

    fseek(archivoOriginal, comienzoImagen, SEEK_SET);
    fseek(archivoNuevo, comienzoImagen, SEEK_SET);

    if(argCod==12)
        recortar(archivoOriginal, archivoNuevo, metadata_entrada, metadata_salida);
    else if(argCod == 11 || argCod==10)
        rotarImagen(archivoOriginal, archivoNuevo, metadata_entrada, metadata_salida, argCod);
    else
    {
        while(fread(&px.pixel, sizeof(unsigned char), 3, archivoOriginal))
        {
            if(argCod<3)
            {
                // Los codigos 1 y 2 corresponden a la modificacion de contraste para lo cual necesitamos los valores maximos y minimos de cada px
                for (int i = 0; i < 3; i++)
                {
                    if (px.pixel[i] < min_value)
                        min_value = MIN(px.pixel[i], min_value);
                    if (px.pixel[i] > max_value)
                        max_value = MAX(px.pixel[i], min_value);
                }
            }

            aplicarFiltro(&px, argCod, min_value, max_value);
            fwrite(&px.pixel, sizeof(unsigned char), 3, archivoNuevo);
        }
    }

    fclose(archivoOriginal);

    return TODO_OK;
}

int leerMetadata(char file[], t_metadata *metadata)
{
    // Lee la metadata de la imagen obtenida
    FILE *img;

    img = fopen(file,"rb");

    fseek(img, 2, SEEK_SET);
    fread(&metadata->tamArchivo, sizeof(unsigned int), 1, img);

    fseek(img, 14, SEEK_SET);
    fread(&metadata->tamEncabezado, sizeof(unsigned int), 1, img);

    fseek(img, 10, SEEK_SET);
    fread(&metadata->comienzoImagen, sizeof(unsigned int), 1, img);

    fseek(img, 18, SEEK_SET);
    fread(&metadata->ancho, sizeof(unsigned int), 1, img);
    fseek(img, 22, SEEK_SET);
    fread(&metadata->alto, sizeof(unsigned int), 1, img);

    fseek(img, 28, SEEK_SET);
    fread(&metadata->profundidad, sizeof(unsigned short), 1, img);

    fclose(img);
    return TODO_OK;
}

void invertirColores(t_pixel *px)
{
    px->pixel[0] = MIN(255,(~px->pixel[0]));
    px->pixel[1] = MIN(255,(~px->pixel[1]));
    px->pixel[2] = MIN(255,(~px->pixel[2]));
}

void escalaDeGrises(t_pixel *px)
{
    float promedio = MIN(255,((px->pixel[0] + px->pixel[1] + px->pixel[2]) / 3));

    px->pixel[0] = (promedio);
    px->pixel[1] = (promedio);
    px->pixel[2] = (promedio);
}

void aumentarContraste(t_pixel *px, int min, int max) {
    float contraste_actual = (max - min) / (float)(max + min);
    float nuevo_contraste = contraste_actual * 1.25; // Aumentar en un 25%

    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}

void disminuirContraste(t_pixel *px, int min, int max) {
    float contraste_actual = (max - min) / (float)(max + min);
    float nuevo_contraste = contraste_actual * 0.75;

    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}

void aumentarColor(t_pixel *px, int color)
{
    px->pixel[color]= MIN(255, ((int)px->pixel[color] + (px->pixel[color] / 2)));
}

void aumentarColorAleatorio(t_pixel *px)
{
    srand(time(NULL));
    int colorAleatorio = rand() % 3;

    switch (colorAleatorio)
    {
        case 0:
            // Aumentar purpura
            aumentarColor(px, 2); // Aumentar rojo
            aumentarColor(px, 0); // Aumentar azul
            break;

        case 1:
            // Aumentar cian
            aumentarColor(px, 1); // Aumentar verde
            aumentarColor(px, 0); // Aumentar azul
            break;

        case 2:
            // Aumentar amarillo
            aumentarColor(px, 2); // Aumentar rojo
            aumentarColor(px, 1); // Aumentar verde
            break;
    }
}


void reducirContraste(t_pixel *px, int min, int max) {
    float contraste_actual = (max - min) / (float)(max + min);
    float nuevo_contraste = contraste_actual * 0.75;

    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}

void recortar(FILE *entrada, FILE *salida, t_metadata *metadata_entrada, t_metadata *metadata_salida)
{
    unsigned int width, height, nWidth, nHeight, inicioImg;
    int i, j;

    t_pixel px;

    fseek(entrada, 10, SEEK_SET);
    fread(&inicioImg, sizeof(unsigned int), 1, entrada);
    fseek(entrada, 18, SEEK_SET);
    fread(&width, sizeof(unsigned int), 1, entrada);
    fread(&height, sizeof(unsigned int), 1, entrada);

    fseek(entrada, inicioImg, SEEK_SET);
    fseek(salida, inicioImg, SEEK_SET);

    nWidth = (width/2);
    nHeight = (height/2);

    for (i = 0; i< nHeight; i++)
    {
        for (j = 0; j < nWidth; j++)
        {
            fread(px.pixel, sizeof(unsigned char), TAM_PIXEL, entrada);
            fwrite(px.pixel, sizeof(unsigned char), TAM_PIXEL, salida);
        }
        fseek(entrada, (width - nWidth) * TAM_PIXEL, SEEK_CUR);
    }

    fseek(salida, 18, SEEK_SET);
    fwrite(&nWidth, sizeof(unsigned int), 1, salida);
    fwrite(&nHeight, sizeof(unsigned int), 1, salida);

    fclose(entrada);
    fclose(salida);
}

void rotarImagen(FILE *entrada, FILE *salida, t_metadata *metadata_entrada, t_metadata *metadata_salida, int argCod)
{
    unsigned char byte;
    unsigned int height, width, nWidth, nHeight, inicioImg;

    int tam;

    fseek(entrada, 10, SEEK_SET);
    fread(&inicioImg, sizeof(unsigned int), 1, entrada);

    fseek(entrada, 18, SEEK_SET);
    fread(&width, sizeof(unsigned int), 1, entrada);
    fread(&height, sizeof(unsigned int), 1, entrada);

    t_pixel vEntrada[width*height];
    t_pixel vSalida[width*height];

    tam = width*height;

    nWidth=height;
    nHeight=width;

    fseek(entrada, 0, SEEK_SET);
    fseek(salida, 0, SEEK_SET);

    for (int i=0; i<inicioImg; i++)
    {
        fread(&byte, sizeof(unsigned char), 1, entrada);
        fwrite(&byte, sizeof(unsigned char), 1, salida);
    }

    fseek(salida, 18, SEEK_SET);
    fwrite(&nWidth, sizeof(unsigned int), 1, salida);
    fwrite(&nHeight, sizeof(unsigned int), 1, salida);


    fseek(entrada, inicioImg, SEEK_SET);
    fseek(salida, inicioImg, SEEK_SET);
    for(int i=0;i<tam;i++)
        fread(vEntrada[i].pixel, sizeof(t_pixel), 1, entrada);

    for(int y = 0; y < nHeight; y++)
    {
        for(int x = 0; x < nWidth; x++)
        {
            (argCod==10) ? (vSalida[y * nWidth + x] = vEntrada[x * nHeight + (nHeight - y - 1)]) : (vSalida[y * nWidth + x] = vEntrada[(nWidth - x - 1) * nHeight + y]); /*(para el otro lado)*/

        }
    }

    for(int i=0;i<tam; i++)
        fwrite(vSalida[i].pixel, sizeof(t_pixel), 1, salida);

}
