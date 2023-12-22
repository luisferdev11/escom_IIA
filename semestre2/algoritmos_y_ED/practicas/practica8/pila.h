#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodoPila {
    int dato;
    struct NodoPila* siguiente;
} NodoPila;

typedef NodoPila* Pila;

void push(Pila* pila, int valor);
int pop(Pila* pila);
bool isEmpty(Pila pila);


