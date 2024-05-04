/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Bonachera
    Nombre: Ornella
    DNI: 46119546
    Entrega:
    -----------------
    Apellido: Pityla
    Nombre: Damian
    DNI:
    Entrega:
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
    t_metadata cabeceraNuevo, cabeceraOriginal;

    char nombreImgOriginal[256], nombreImgNueva[256];
    int pos, argCod;

    pos = posicionBmp(argc, argv);
    // Devuelve la posicion del archivo bmp en caso de ser encontrado, -1 si hay mas de un archivo y 0 si no encuentra ninguno
    if(pos==-1)
    {
        printf("Existe mas de un archivo BMP");
        return 1;
    }else if(pos==0)
    {
        printf("No se encontro ningun archivo BMP");
        return 1;
    }
    nombreImgOriginal[0] = '\0';
    strcpy(nombreImgOriginal, argv[pos]);
    //Copia el nombre del archivo en la variable nombreImgOriginal
    printf("\n Nombre del archivo: (%s)\n", nombreImgOriginal);

    for(int j=0; j<argc; j++)
    {
        printf("Argumento: (%s)",argv[j]);
    }

    for(int i=1; i<argc; i++)
    // Corremos el proceso tantas veces como comandos con filtros aparezcan
    {
        // printf("Entro aca\n");
        // printf("i %d pos %d\n", i, pos);
        if(i!=pos){
            // printf("aaaaaaaaa");
            argCod = validarDevolverCodigo(argv[i]);
            printf("(%d)", argCod);
            // Valida si el comando a ejecutar es valido
        if(argCod==-1)
            printf("Argumento numero: %d no existente\n", i);
        else
        {
            printf("Entro aca");
            eliminarPrimerosDosCaracteres(argv[i]);

            nombreImgNueva[0] = '\0';

            strcat(nombreImgNueva,"estudiante_");
            strcat(nombreImgNueva,argv[i]);
            strcat(nombreImgNueva,".bmp");
            // Crea el nombre del archivo que corresponde y lo guardaen la variable nombreImgNueva
            printf("\n Nombre del archivo: %s \n", nombreImgNueva);

            FILE *pImagenNueva = fopen(nombreImgNueva, "wb");
            // Crea el archivo de la imagen nueva
            if(pImagenNueva== NULL) {
                printf("Error al abrir el archivo de salida");
                return -3;
            }

            leerCabecera(nombreImgOriginal, &cabeceraOriginal);
            // Guardamos la cabecera de la imagen original solo por si debemos hacerle modificaciones
            escribirCabecera(pImagenNueva, nombreImgOriginal);
            // Escribimos la cabecera en la imagen nueva
            escribirDatos(pImagenNueva, nombreImgOriginal, argCod);
            // Escribimos los pixeles de la imagen original en la nueva
            leerCabecera(nombreImgNueva, &cabeceraNuevo);
            // Leemos la cebcera de la imagen nueva

            fclose(pImagenNueva);
        }
      }
    }
    return 0;
}

int posicionBmp(const int argc, char *argv[])
{
    int cant=0, encontrado=0;
    char *extension;
    for (int i = 1; i < argc; i++) {

        // Verificar si el argumento termina con ".bmp" usando strrchr
        // strrchr devuelve un puntero a la última aparición de un carácter en una cadena
        // Aquí estamos buscando la última aparición de "." en el argumento
        extension = strrchr(argv[i], '.');

        // Si encontramos una extensión y es ".bmp", regresamos 1
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
    // Opciones de modificar dimensiones (Modifica dimensiones)
    if(!strcmpi(arg, "--recortar-imagen")) return 8;
    if(!strcmpi(arg, "--rotar-derecha")) return 9;
    if(!strcmpi(arg, "--rotar-izquierda")) return 9;

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
        case 8:
        case 9:
        case 10:
            printf("Estamos trabajando en esta funcionalidad.");
            break;
        default:
            return 1;
    }
    return 0;
}

void eliminarPrimerosDosCaracteres(char *cadena) {
    size_t longitud = strlen(cadena);

    // Desplaza la cadena dos caracteres hacia la izquierda
    for (size_t i = 2; i <= longitud; i++) {
        cadena[i - 2] = cadena[i];
    }
}

int escribirCabecera(FILE *archivoNuevo, char nombreImgOriginal[])
{
    // Copia TODOS los datos de la cabecera del archivo original al nuevo
    FILE *archivoOriginal;

    archivoOriginal = fopen(nombreImgOriginal,"rb");

    if (archivoOriginal == NULL || archivoNuevo == NULL) {
        perror("Error opening file");
        return 1;
    }

    unsigned char byte[3];

    printf("Escribiendo cabecera...\n");
    for(int i=0; i<54;i++){
        fread(&byte, sizeof(unsigned char), 1, archivoOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, archivoNuevo);
    }
    printf("Cabecera escrita correctamente.\n");
    fclose(archivoOriginal);

    return 0;
}

int escribirDatos(FILE *archivoNuevo, char nombreImgOriginal[], int argCod)
{
    // Escribe los pixeles que componen la imagen
    t_pixel px;

    unsigned char min_value = 255;
    unsigned char max_value = 0;

    FILE *archivoOriginal;

    archivoOriginal = fopen(nombreImgOriginal,"rb");

    if (archivoOriginal == NULL || archivoNuevo == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(archivoOriginal, 54, SEEK_SET);
    fseek(archivoNuevo, 54, SEEK_SET);



    while(fread(&px.pixel, sizeof(unsigned char), 3, archivoOriginal))
    {
        if(argCod<3){
        // Los codigos 1 y 2 corresponden a la modificacion de contraste para lo cual necesitamos los valores maximos y minimos de cada px
            for (int i = 0; i < 3; i++)
            {
                if (px.pixel[i] < min_value) { min_value = MIN(px.pixel[i], min_value); }
                if (px.pixel[i] > max_value) { max_value = MAX(px.pixel[i], min_value); }
            }
        }

        aplicarFiltro(&px, argCod, min_value, max_value);
        fwrite(&px.pixel, sizeof(unsigned char), 3, archivoNuevo);
    }

    fclose(archivoOriginal);

    return 0;
}

int leerCabecera(char file[], t_metadata *cabecera)
{
    FILE *img;

    img = fopen(file,"rb");

    printf("\n\n--------");
    printf("Filename: %s\n",file);

    fseek(img, 2, SEEK_SET);
    fread(&cabecera->tamArchivo, sizeof(unsigned int), 1, img);

    fseek(img, 14, SEEK_SET);
    fread(&cabecera->tamEncabezado, sizeof(unsigned int), 1, img);

    fseek(img, 10, SEEK_SET);
    fread(&cabecera->comienzoImagen, sizeof(unsigned int), 1, img);

    fseek(img, 18, SEEK_SET);
    fread(&cabecera->ancho, sizeof(unsigned int), 1, img);

    fseek(img, 22, SEEK_SET);
    fread(&cabecera->alto, sizeof(unsigned int), 1, img);

    fseek(img, 28, SEEK_SET);
    fread(&cabecera->profundidad, sizeof(unsigned short), 1, img);

    printf("Tamaño de archivo: %u bytes\n", cabecera->tamArchivo);
    printf("Tamaño de cabecera: %u bytes\n", cabecera->tamEncabezado);
    printf("Alto: %u bytes\n", cabecera->alto);
    printf("Ancho: %u bytes\n", cabecera->ancho);
    printf("Comienzo de imagen: byte %u\n", cabecera->comienzoImagen);
    printf("Profundidad: %u bits\n", cabecera->profundidad);

    fclose(img);
    return 0;
}

int modificarDimensiones(FILE *file, unsigned int w, unsigned int h)
{
    fseek(file, 18, SEEK_SET);
    fwrite(&w, sizeof(unsigned int), 1, file);

    fseek(file, 22, SEEK_SET);
    fwrite(&h, sizeof(unsigned int), 1, file);

    return 0;
}

void invertirColores(t_pixel *px)
{
    px->pixel[0] = (unsigned char)(~px->pixel[0]);
    px->pixel[1] = (unsigned char)(~px->pixel[1]);
    px->pixel[2] = (unsigned char)(~px->pixel[2]);
}

void escalaDeGrises(t_pixel *px)
{
    float promedio = ((px->pixel[0] + px->pixel[1] + px->pixel[2]) / 3);

    px->pixel[0] = (unsigned char)(promedio);
    px->pixel[1] = (unsigned char)(promedio);
    px->pixel[2] = (unsigned char)(promedio);
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

void reducirContraste(t_pixel *px, int min, int max) {
    float contraste_actual = (max - min) / (float)(max + min);
    float nuevo_contraste = contraste_actual * 0.75;

    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}
