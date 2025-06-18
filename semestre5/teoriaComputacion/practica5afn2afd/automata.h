#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Para strcmp

#include "cadenas.h"

// Valor especial para representar transiciones epsilon
// NOTA: El símbolo epsilon siempre se incluye automáticamente en el alfabeto
// No es necesario incluirlo en la lista de símbolos del archivo.
#define EPSILON_SYMBOL "epsilon"

// Estructura para representar una lista enlazada de transiciones
typedef struct nodo_transicion {
    int destino;
    struct nodo_transicion *siguiente;
} NodoTransicion;

// Estructura principal para el AFN
typedef struct {
    int numEstados;
    int numSimbolos;
    char **estados;
    char **alfabeto;
    int estadoInicial;
    int *finales;
    int tieneEpsilon;
    int indiceEpsilon;

    // Matriz de transiciones[estado][simbolo] -> lista enlazada de estados destino
    NodoTransicion ***transiciones;
} AFN;

typedef struct nodo_recorrido {
    int *estados;
    int longitud;
    char *simbolos;
    struct nodo_recorrido *siguiente;
} NodoRecorrido;

typedef struct {
    int *estados;
    int numEstados;
    int capacidad;
} ConjuntoEstados;

// Gestión del AFN
AFN *crearAFN(int numEstados, int numSimbolos);
AFN *cargarAFN(const char *nombreArchivo);
void liberarAFN(AFN *afn);
void imprimirAFN(AFN *afn);

// Gestión de transiciones
void agregarTransicion(AFN *afn, char *origen, char *simbolo, char *destino);
int indiceSimbolo(AFN *afn, char *simbolo);
int indiceEstado(AFN *afn, char *estado);
int esEpsilon(AFN *afn, int indiceSimbolo);

// Operaciones para transiciones epsilon
ConjuntoEstados *crearConjuntoEstados(int capacidadInicial);
void liberarConjuntoEstados(ConjuntoEstados *conjunto);
void agregarEstado(ConjuntoEstados *conjunto, int estado);
int contieneEstado(ConjuntoEstados *conjunto, int estado);
ConjuntoEstados *clausuraEpsilon(AFN *afn, int estado);
ConjuntoEstados *clausuraEpsilonConjunto(AFN *afn, ConjuntoEstados *conjunto);

// Algoritmos de búsqueda y auxiliares
void dfs(AFN *afn, int estadoActual, const char *cadena, int pos, int longitud,
         int *camino, char *caminoSimbolos, int indiceCamino, NodoRecorrido **listaRecorridos);
void explorarTransicionesEpsilon(AFN *afn, int estadoActual, const char *cadena, int pos, int longitud,
                                 int *camino, char *caminoSimbolos, int indiceCamino,
                                 NodoRecorrido **listaRecorridos);
void guardarRecorrido(AFN *afn, int *camino, char *simbolos, int longitud,
                      NodoRecorrido **listaRecorridos);

// Representación e impresión
void imprimirRecorridoConNombres(AFN *afn, int *camino, char *simbolos, int longitud);
void imprimirRecorridosConNombres(AFN *afn, NodoRecorrido *lista);

#endif
