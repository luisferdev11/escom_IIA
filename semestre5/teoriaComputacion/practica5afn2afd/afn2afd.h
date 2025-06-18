#ifndef AFN2AFD_H
#define AFN2AFD_H

#include "automata.h"
#include "cadenas.h"

// Estructura para representar un conjunto de estados en el AFD
typedef struct {
    int *estados;    // Array de índices de estados originales
    int numEstados;  // Número de estados en el conjunto
    char *nombre;    // Nombre del nuevo estado en el AFD
    int esFinal;     // Indica si este conjunto contiene algún estado final
} EstadoAFD;

// Estructura para almacenar una lista de conjuntos de estados (estados del AFD)
typedef struct {
    EstadoAFD **estados;  // Array de punteros a estados AFD
    int numEstados;       // Número de estados en la lista
    int capacidad;        // Capacidad actual del array
} ListaEstadosAFD;

// Estructura para representar transiciones del AFD
typedef struct {
    char *origen;     // Nombre del estado origen
    char simbolo[2];  // Símbolo de la transición
    char *destino;    // Nombre del estado destino
} TransicionAFD;

// Estructura para lista de transiciones
typedef struct {
    TransicionAFD **transiciones;
    int numTransiciones;
    int capacidad;
} ListaTransicionesAFD;

// Funciones para manejo de estados AFD
ListaEstadosAFD *crearListaEstadosAFD(int capacidadInicial);
void liberarListaEstadosAFD(ListaEstadosAFD *lista);
EstadoAFD *crearEstadoAFD(ConjuntoEstados *conjunto, char *nombre, AFN *afnOriginal);
void liberarEstadoAFD(EstadoAFD *estado);
int agregarEstadoAFD(ListaEstadosAFD *lista, EstadoAFD *estado);
int buscarEstadoAFD(ListaEstadosAFD *lista, ConjuntoEstados *conjunto);
void imprimirEquivalenciasEstados(ListaEstadosAFD *estadosAFD, AFN *afnOriginal);

// Funciones para manejo de transiciones AFD
ListaTransicionesAFD *crearListaTransicionesAFD(int capacidadInicial);
void liberarListaTransicionesAFD(ListaTransicionesAFD *lista);
void agregarTransicionAFD(ListaTransicionesAFD *lista, char *origen, char *simbolo, char *destino);
char *buscarTransicionAFD(ListaTransicionesAFD *lista, char *origen, char simbolo);

// Funciones para el algoritmo de conversión
ConjuntoEstados *mover(AFN *afn, ConjuntoEstados *estados, int simbolo);
void convertirAFNaAFD(AFN *afn, ListaEstadosAFD **estadosAFD, ListaTransicionesAFD **transicionesAFD);
void guardarAFD(ListaEstadosAFD *estadosAFD, ListaTransicionesAFD *transicionesAFD, AFN *afnOriginal, char *nombreArchivo);

// Función para procesar una cadena en el AFD
int procesarCadenaAFD(ListaEstadosAFD *estadosAFD, ListaTransicionesAFD *transicionesAFD, char *estadoInicial, const char *cadena);

#endif  // AFN2AFD_H