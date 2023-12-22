#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arboles.h"
#include "cola.h"
#include "lista_circular.h"

typedef struct {
    char caracter;
    char* codigo;
} CodigoHuffman;

Arbol crearArbolHuffman(ListaCircular* lista);
void generarCodigosDFS(Arbol raiz, char* codigo, int longitud, CodigoHuffman* codigos, int* indice);
void generarCodigosHuffman(Arbol arbolHuffman, CodigoHuffman* codigos, int* numCodigos);
void codificarTexto(const char* nombreArchivoEntrada, const char* nombreArchivoSalida, CodigoHuffman* codigos, int numCodigos);
void decodificarTextoConCola(const char* nombreArchivoCodificado, const char* nombreArchivoDecodificado, Arbol arbolHuffman);
