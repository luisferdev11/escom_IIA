#include <stdio.h>
#include <stdlib.h>

// Estructura para los nodos de la lista doblemente enlazada
struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
};

// Función para agregar un nuevo nodo al final de la lista
void agregarAlFinal(struct Nodo** cabeza, int nuevoDato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* ultimo = *cabeza;
    nuevoNodo->dato = nuevoDato;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
        return;
    }

    while (ultimo->siguiente != NULL) {
        ultimo = ultimo->siguiente;
    }

    ultimo->siguiente = nuevoNodo;
    nuevoNodo->anterior = ultimo;
}

// Función para imprimir todos los elementos de la lista
void imprimirLista(struct Nodo* nodo) {
    while (nodo != NULL) {
        printf("%d ", nodo->dato);
        nodo = nodo->siguiente;
    }
    printf("\n");
}

// Función para intercambiar los datos de dos nodos
void intercambiar(struct Nodo* a, struct Nodo* b) {
    int temp = a->dato;
    a->dato = b->dato;
    b->dato = temp;
}

// Función para ordenar la lista doblemente enlazada
void ordenaSeleccionListaDoble(struct Nodo* cabeza) {
    struct Nodo *i, *j;
    for (i = cabeza; i != NULL && i->siguiente != NULL; i = i->siguiente) {
        for (j = i->siguiente; j != NULL; j = j->siguiente) {
            if (j->dato < i->dato) {  // Cambia "<" a ">" para ordenar de forma descendente
                intercambiar(i, j);
            }
        }
    }
}

int main() {
    struct Nodo* cabeza = NULL;

    // Agregar datos a la lista
    agregarAlFinal(&cabeza, 4);
    agregarAlFinal(&cabeza, 3);
    agregarAlFinal(&cabeza, 1);
    agregarAlFinal(&cabeza, 2);

    printf("Lista antes de ordenar:\n");
    imprimirLista(cabeza);

    ordenaSeleccionListaDoble(cabeza);

    printf("Lista después de ordenar:\n");
    imprimirLista(cabeza);

    return 0;
}
