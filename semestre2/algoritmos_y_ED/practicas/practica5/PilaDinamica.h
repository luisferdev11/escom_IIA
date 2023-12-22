#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char valor;
} Data;

struct Nodo {
    Data info;
    struct Nodo* siguiente;
};

typedef struct {
    struct Nodo* cima;
    int cursor;
} Pila;

void crearPila(Pila*);
bool apilar(Pila*, Data);
Data desapilar(Pila*);
void consultarCima(Pila);
void destruirPila(Pila*);
void vaciarPila(Pila*);
bool estaVacia(Pila);
