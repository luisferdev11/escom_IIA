#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nombre;
    int edad;
} Persona;

struct Nodo {
    Persona persona;
    struct Nodo *siguiente;
};

typedef struct Nodo *Lista;

Persona crearPersona(char *nombre, int edad) {
    Persona p;
    p.nombre = strdup(nombre);  // Duplica la cadena para evitar problemas de punteros
    p.edad = edad;
    return p;
}

void insertar(Lista *L, Persona persona) {
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevoNodo->persona = persona;

    if (*L == NULL) {
        nuevoNodo->siguiente = nuevoNodo;  // Apunta a sí mismo si la lista está vacía
        *L = nuevoNodo;
    } else {
        struct Nodo *temp = *L;
        while (temp->siguiente != *L) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
        nuevoNodo->siguiente = *L;
    }
}

void imprimirLista(Lista L) {
    if (L == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    struct Nodo *temp = L;
    do {
        printf("Nombre: %s, Edad: %d\n", temp->persona.nombre, temp->persona.edad);
        temp = temp->siguiente;
    } while (temp != L);
}

void imprimirListaInversa(Lista *L) {
    if (*L == NULL) {
        printf("La lista está vacía.\n");
        return;
    }
    Lista *aux = L;
    L = &((*L)->siguiente);

    printf("%s %d\n", (*aux)->persona.nombre, (*aux)->persona.edad);
    printf("%s %d\n", (*L)->persona.nombre, (*L)->persona.edad);

    if (*L != *aux) {
        // puts("Entra lista inversa:");
        imprimirListaInversa(&((*L)->siguiente));
        printf("%s %d\n", (*L)->persona.nombre, (*L)->persona.edad);
    }
}

int main() {
    Lista miLista = NULL;

    insertar(&miLista, crearPersona("Alice", 30));
    insertar(&miLista, crearPersona("Bob", 25));
    insertar(&miLista, crearPersona("Charlie", 35));

    printf("Lista Original:\n");
    imprimirLista(miLista);

    printf("\nLista Inversa:\n");
    imprimirListaInversa(&miLista);

    return 0;
}
