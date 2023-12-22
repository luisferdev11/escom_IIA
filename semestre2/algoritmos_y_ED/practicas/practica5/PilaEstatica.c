/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
8-nov-2023
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char caracter;
} Dato;

struct Nodo {
    Dato info;
    struct Nodo* siguiente;
};

bool estaLlena(int tope, int tamano) {
    return tope == tamano - 1;
}

bool estaVacia(struct Nodo* cima) {
    return cima == NULL;
}

void push(struct Nodo** cima, char valor) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("Desbordamiento de pila: no se pudo asignar memoria\n");
        return;
    }
    nuevoNodo->info.caracter = valor;
    nuevoNodo->siguiente = *cima;
    *cima = nuevoNodo;
}

char pop(struct Nodo** cima) {
    if (estaVacia(*cima)) {
        return '\0';  // Valor nulo para indicar pila vacía
    } else {
        struct Nodo* temp = *cima;
        char valor = temp->info.caracter;
        *cima = (*cima)->siguiente;
        free(temp);
        return valor;
    }
}

// Función para comprobar si dos paréntesis son del mismo tipo
bool sonParesCorrespondientes(char caracter1, char caracter2) {
    return (caracter1 == '(' && caracter2 == ')') ||
           (caracter1 == '{' && caracter2 == '}') ||
           (caracter1 == '[' && caracter2 == ']');
}

bool estaBalanceada(char* expresion) {
    struct Nodo* cima = NULL;

    for (int i = 0; expresion[i] != '\0'; i++) {
        char caracterActual = expresion[i];

        if (caracterActual == '(' || caracterActual == '{' || caracterActual == '[') {
            push(&cima, caracterActual);
        } else if (caracterActual == ')' || caracterActual == '}' || caracterActual == ']') {
            if (estaVacia(cima) || !sonParesCorrespondientes(pop(&cima), caracterActual)) {
                return false;
            }
        }
    }

    bool balanceada = estaVacia(cima);
    while (!estaVacia(cima)) {
        pop(&cima);
    }
    return balanceada;
}

int main() {
    FILE* archivo = fopen("exp.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    char expresion[MAX];
    if (fgets(expresion, MAX, archivo) != NULL) {
        if (estaBalanceada(expresion) == true) {
            printf("La expresión está balanceada.\n");
        } else {
            printf("La expresión no está balanceada.\n");
        }
    }

    fclose(archivo);
    return 0;
}