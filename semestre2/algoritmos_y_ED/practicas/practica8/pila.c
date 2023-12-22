#include "pila.h"

void push(Pila* pila, int valor) {
    NodoPila* nuevoNodo = (NodoPila*)malloc(sizeof(NodoPila));
    if (nuevoNodo == NULL) {
        perror("No se pudo asignar memoria para un nuevo nodo de pila");
        exit(EXIT_FAILURE);
    }
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = *pila;
    *pila = nuevoNodo;
}

int pop(Pila* pila) {
    if (isEmpty(*pila)) {
        perror("Pop en pila vacía");
        exit(EXIT_FAILURE);
    }
    NodoPila* temp = *pila;
    int valor = temp->dato;
    *pila = (*pila)->siguiente;
    free(temp);
    return valor;
}

bool isEmpty(Pila pila) {
    return pila == NULL;
}
