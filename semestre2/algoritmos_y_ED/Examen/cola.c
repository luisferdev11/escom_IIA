
#include "cola.h"

// Función para crear una nueva cola
Cola* crearCola() {
    Cola* nuevaCola = (Cola*)malloc(sizeof(Cola));
    if (!nuevaCola) {
        perror("Error al crear la cola");
        return NULL;
    }
    nuevaCola->frente = nuevaCola->fin = NULL;
    return nuevaCola;
}

// Función para crear un nuevo nodo de cola
static NodoCola* crearNodoCola(Dato_cola dato) {
    NodoCola* nuevoNodo = (NodoCola*)malloc(sizeof(NodoCola));
    if (!nuevoNodo) {
        perror("Error al crear el nodo de cola");
        return NULL;
    }
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

// Función para encolar (insertar) un elemento en la cola
void encolar(Cola* cola, Dato_cola dato) {
    NodoCola* nuevoNodo = crearNodoCola(dato);
    if (!cola->fin) {
        cola->frente = cola->fin = nuevoNodo;
        return;
    }
    cola->fin->siguiente = nuevoNodo;
    cola->fin = nuevoNodo;
}

// Función para desencolar (eliminar) un elemento de la cola
bool desencolar(Cola* cola, Dato_cola* datoSalida) {
    if (esColaVacia(cola)) return false;

    NodoCola* temp = cola->frente;
    *datoSalida = temp->dato;
    cola->frente = cola->frente->siguiente;

    if (cola->frente == NULL) {
        cola->fin = NULL;
    }

    free(temp);
    return true;
}

// Función para observar el elemento frontal de la cola sin eliminarlo
bool frenteCola(Cola* cola, Dato_cola* datoSalida) {
    if (esColaVacia(cola)) return false;

    *datoSalida = cola->frente->dato;
    return true;
}

// Función para comprobar si la cola está vacía
bool esColaVacia(Cola* cola) {
    return cola->frente == NULL;
}

// Función para liberar la memoria de la cola
void liberarCola(Cola* cola) {
    NodoCola* actual = cola->frente;
    while (actual) {
        NodoCola* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    free(cola);
}

// Función para mostrar los elementos de la cola
void mostrarCola(Cola* cola) {
    NodoCola* actual = cola->frente;
    while (actual) {
        printf("%d ", actual->dato.valor);
        actual = actual->siguiente;
    }
    printf("\n");
}
