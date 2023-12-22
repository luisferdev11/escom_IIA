

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Estructura para el dato almacenado
typedef struct {
    int valor;
} Dato_cola;

// Estructura de un nodo de la cola
typedef struct NodoCola {
    Dato_cola dato;
    struct NodoCola* siguiente;
} NodoCola;

// Estructura de la cola
typedef struct {
    NodoCola* frente;
    NodoCola* fin;
} Cola;

// Prototipos de funciones
Cola* crearCola();
void encolar(Cola* cola, Dato_cola dato);
bool desencolar(Cola* cola, Dato_cola* datoSalida);
bool frenteCola(Cola* cola, Dato_cola* datoSalida);
bool esColaVacia(Cola* cola);
void liberarCola(Cola* cola);
void mostrarCola(Cola* cola);
