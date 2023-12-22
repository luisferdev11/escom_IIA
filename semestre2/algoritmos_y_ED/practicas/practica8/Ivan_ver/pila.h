/*
Luis Fernando Rodriguez Dominguez
Iván Martínez Mendoza
Edgar Marin Montes de Oca
2BV2
Ingenieria en Inteligencia Artificial
8-dic-2023
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct nodoPila {
    int dato;
    struct nodoPila* siguiente;
} NodoPila;

typedef NodoPila* Pila;

void inicializarPila(Pila* pila) {
    *pila = NULL;
}

bool estaVacia(Pila pila) {
    return pila == NULL;
}

void push(Pila* pila, int valor) {
    NodoPila* nuevoNodo = (NodoPila*)malloc(sizeof(NodoPila));
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = *pila;
    *pila = nuevoNodo;
}

int pop(Pila* pila) {
    if (estaVacia(*pila)) {
        printf("Pila vac�a\n");
        return -1;  // O manejar el error como prefieras
    }
    int valor = (*pila)->dato;
    NodoPila* nodoAEliminar = *pila;
    *pila = (*pila)->siguiente;
    free(nodoAEliminar);
    return valor;
}
