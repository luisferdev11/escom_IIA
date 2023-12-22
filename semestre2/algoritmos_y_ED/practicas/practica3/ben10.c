/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
6-oct-2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10000
#define RANGO_MAXIMO 459565

int* crearArreglo() {
    int* arreglo = calloc(TAM, sizeof(int));
    srand(time(NULL));
    if (arreglo != NULL) {
        for (int i = 0; i < TAM; i++) {
            arreglo[i] = (rand() % RANGO_MAXIMO);
        }
    } else {
        puts("Error, no hay memoria suficiente");
        exit(1);
    }

    return arreglo;
}

/*
    Funcion que destruye un arreglo dinamico
    @param arreglo Un arreglo de enteros por referencia
    @return Nada
*/

void destruirArreglo(int* arreglo) {
    free(arreglo);
}

void ordenarSeleccion(int* arreglo) {
    int aux = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = i + 1; j < TAM; j++) {
            if (arreglo[j] < arreglo[i]) {
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
}

void ordenarInsercion(int* arreglo) {
    int i, j;
    int aux;
    for (i = 1; i < TAM; i++) {
        aux = arreglo[i];
        j = i - 1;
        // Mover los elementos del arreglo[0..i-1] que son mayores que la clave
        while (j >= 0 && arreglo[j] < aux) {
            arreglo[j + 1] = arreglo[j];
            j = j - 1;
        }
        arreglo[j + 1] = aux;
    }
}

// toda operacion de consulta debe ser una copia del arreglo
void imprimeArreglo(int arreglo[TAM]) {
    for (int k = 0; k < TAM; k++) {
        printf("Arreglo[%d]=%d\n", k, arreglo[k]);
    }
}

void main() {
    puts("Bienvenido...");
    int* miArray = crearArreglo();
    puts("Arreglo desordenado");
    imprimeArreglo(miArray);
    ordenarSeleccion(miArray);
    puts("Arreglo ordenado por seleccion");
    imprimeArreglo(miArray);
    ordenarInsercion(miArray);
    puts("Arreglo ordenado por insercion");
    imprimeArreglo(miArray);
    destruirArreglo(miArray);
    puts("Fin del programa");
}