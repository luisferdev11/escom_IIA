#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <stdio.h>
#include <stdlib.h>

#include "cadenas.h"

typedef struct nodo_transicion {
    int destino;
    struct nodo_transicion *siguiente;
} NodoTransicion;

typedef struct {
    int numEstados;
    int numSimbolos;
    char **estados;
    char **alfabeto;
    int estadoInicial;
    int *finales;

    NodoTransicion ***transiciones;
} AFN;

typedef struct nodo_recorrido {
    int *estados;    // Secuencia de índices de estados recorridos
    int longitud;    // Cantidad de estados en el recorrido
    char *simbolos;  // Cadena de símbolos consumidos (longitud = recorrido - 1)
    struct nodo_recorrido *siguiente;
} NodoRecorrido;

// Prototipos de funciones del módulo AFN

// Carga un AFN desde un archivo con el formato especificado
AFN *cargarAFN(const char *nombreArchivo);

void liberarAFN(AFN *afn);

void agregarTransicion(AFN *afn, char *origen, char *simbolo, char *destino);

int indiceSimbolo(AFN *afn, char *simbolo);

int indiceEstado(AFN *afn, char *estado);

void dfs(AFN *afn, int estadoActual, const char *cadena, int pos, int longitud,
         int *camino, char *caminoSimbolos, int indiceCamino, NodoRecorrido **listaRecorridos);

void imprimirRecorridoConNombres(AFN *afn, int *camino, char *simbolos, int longitud);
void imprimirRecorridosConNombres(AFN *afn, NodoRecorrido *lista);

#endif
