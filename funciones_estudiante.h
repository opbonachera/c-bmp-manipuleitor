#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED

#include "constantes.h"
#include "estructuras.h"

int solucion(int argc, char* argv[]);

int leerMetadata(char [], t_metadata *);
int escribirMetadata(FILE *archivoNuevo, char[], unsigned int);
int escribirDatos(FILE *archivoNuevo, char[], int, unsigned int, t_metadata*, t_metadata*);
int crearImagen(int, char*[]);

void eliminarPrimerosDosCaracteres(char *);
int validarDevolverCodigo(char []);
int posicionBmp(const int, char *[]);

int aplicarFiltro(t_pixel *, int, int, int);
void aumentarColor(t_pixel *, int);
void aumentarColorAleatorio(t_pixel *);
void escalaDeGrises(t_pixel *);
void aumentarContraste(t_pixel *, int, int);
void invertirColores(t_pixel *);
void aumentarContraste(t_pixel *, int, int);
void reducirContraste(t_pixel *, int, int);
void recortar(FILE *, FILE *, t_metadata *, t_metadata *);
void rotarImagen(FILE*, FILE*, t_metadata*, t_metadata*, int);
//void recortar(FILE *)

#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
