#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;
} Data;

struct Nodo {
    int elemento;
    struct Nodo* siguiente;
};

struct Cola {
    struct Nodo* cabecera;
    struct Nodo* final;
};

struct Cola* crearCola() {
    struct Cola* cola = (struct Cola*)malloc(sizeof(struct Cola));
    cola->cabecera = NULL;
    cola->final = NULL;
    return cola;
}

void encolar(struct Cola* cola, int elemento) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = NULL;
    if (cola->cabecera == NULL) {
        cola->cabecera = nuevoNodo;
        cola->final = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
        cola->final = nuevoNodo;
    }
}

int desencolar(struct Cola* cola) {
    if (cola->cabecera == NULL) {
        printf("La cola esta vacia\n");
        return -1;
    } else {
        int elemento = cola->cabecera->elemento;
        struct Nodo* aux = cola->cabecera;
        cola->cabecera = aux->siguiente;
        aux->siguiente = NULL;
        free(aux);
        return elemento;
    }
}

// recorre la cola y muestra los elementos
void mostrarCola(struct Cola cola) {
    struct Nodo* aux = cola.cabecera;
    while (aux != NULL) {
        printf("%d ", aux->elemento);
        aux = aux->siguiente;
    }
    printf("\n");
}

// esta vacia?
bool estaVacia(struct Cola cola) {
    return cola.cabecera == NULL && cola.final == NULL;
}

int main(int argc, char const* argv[]) {
    /* code */

    // genera cola y checa si esta vacia
    struct Cola* cola = crearCola();
    printf("Esta vacia? %d\n", estaVacia(*cola));
    return 0;
}
