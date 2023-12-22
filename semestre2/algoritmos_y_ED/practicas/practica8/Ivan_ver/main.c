/*
Luis Fernando Rodriguez Dominguez
Iván Martínez Mendoza
Edgar Marin Montes de Oca
2BV2
Ingenieria en Inteligencia Artificial
8-dic-2023
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arboles.c"
#include "pila.h"

int generarPrioridad() {
    return (rand() % 15) + 1;  // Genera un n�mero aleatorio entre 1 y 15
}

// Funci�n para evaluar expresiones posfijas
int evaluarPosfija(const char* expresion) {
    Pila pila;
    inicializarPila(&pila);
    int i;
    for (i = 0; expresion[i]; i++) {
        if (isdigit(expresion[i])) {
            push(&pila, expresion[i] - '0');
        } else {
            int val1 = pop(&pila);
            int val2 = pop(&pila);

            switch (expresion[i]) {
                case '+':
                    push(&pila, val2 + val1);
                    break;
                case '-':
                    push(&pila, val2 - val1);
                    break;
                case '*':
                    push(&pila, val2 * val1);
                    break;
                case '/':
                    push(&pila, val2 / val1);
                    break;
                    // Agrega m�s operadores si es necesario
            }
        }
    }

    return pop(&pila);
}

// Funci�n para calcular el nivel de un nodo
int nivelNodo(Arbol raiz, Dato valor, int nivel) {
    if (raiz == NULL) return 0;
    if (raiz->info.prioridad == valor.prioridad) return nivel;

    int nivelInferior = nivelNodo(raiz->izq, valor, nivel + 1);
    if (nivelInferior != 0) return nivelInferior;

    nivelInferior = nivelNodo(raiz->der, valor, nivel + 1);
    return nivelInferior;
}

// Funci�n para contar la cantidad de hijos de un nodo
int cantidadHijosNodo(Arbol nodo) {
    int contador = 0;
    if (nodo->izq != NULL) contador++;
    if (nodo->der != NULL) contador++;
    return contador;
}

// Funci�n para evaluar y mostrar informaci�n de los nodos
void evaluarYMostrarNodo(Arbol raiz, Arbol nodo, int nivel) {
    if (nodo) {
        int resultado = evaluarPosfija(nodo->info.expresion);
        printf("Prioridad: %d, Nivel: %d, Hijos: %d, Expresion: %s, Resultado: %d\n",
               nodo->info.prioridad, nivel, cantidadHijosNodo(nodo), nodo->info.expresion, resultado);
    }
}

// Funci�n para recorrer, evaluar y mostrar informaci�n de cada nodo
void recorrerEvaluarYMostrar(Arbol raiz, Arbol nodoActual, int nivel) {
    if (nodoActual) {
        recorrerEvaluarYMostrar(raiz, nodoActual->izq, nivel + 1);
        evaluarYMostrarNodo(raiz, nodoActual, nivelNodo(raiz, nodoActual->info, 1));
        recorrerEvaluarYMostrar(raiz, nodoActual->der, nivel + 1);
    }
}

void eliminarTodosLosNodos(Arbol* raiz) {
    if (*raiz) {
        eliminarTodosLosNodos(&((*raiz)->izq));
        eliminarTodosLosNodos(&((*raiz)->der));
        eliminarNodoArbol(raiz, (*raiz)->info);
    }
}

int main() {
    srand(time(NULL));  // Inicializa el generador de n�meros aleatorios

    Arbol bst = NULL;
    int n;
    char expresion[100];

    printf("Ingrese la cantidad de expresiones (1-18): ");
    scanf("%d", &n);
    if (n < 1 || n > 18) {
        printf("N�mero de expresiones fuera de rango.\n");
        return 1;
    }
    int i;
    for (i = 0; i < n; i++) {
        printf("Ingrese la expresion posfija #%d: ", i + 1);
        scanf("%s", expresion);

        Dato valor;
        strcpy(valor.expresion, expresion);
        valor.prioridad = generarPrioridad();

        insertarNodoArbol(&bst, valor);
    }

    // Recorrer, evaluar y mostrar informaci�n de cada nodo
    printf("Ejecutando evaluaciones en orden...\n");
    recorrerEvaluarYMostrar(bst, bst, 0);

    // Eliminar todos los nodos despu�s de la evaluaci�n
    eliminarTodosLosNodos(&bst);

    return 0;
}
