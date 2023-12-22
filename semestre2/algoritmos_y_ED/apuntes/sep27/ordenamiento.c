#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

int* crearArreglo() {
    int* arreglo = calloc(TAM, sizeof(int));
    srand(time(NULL));
    if (arreglo == NULL) {
        printf("No se pudo crear el arreglo");
        exit(1);
    }
    for (int i = 0; i < TAM; i++) {
        arreglo[i] = (rand() % 100) - 1;
    }

    return arreglo;
}

/*
    Función que destruye un arreglo
    @param arreglo: Un arreglo de enteros
    @return nada
*/
void destruirArreglo(int* arreglo) {
    free(arreglo);
}

void ordenaSeleccion(int* arreglo) {
    int aux = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = i + 1; j < TAM; j++) {
            if (arreglo[j] > arreglo[i]) {
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
}

// Todo lo que sea consulta, se pasa por valor y no referencia para no modificar los datos

void imprimeArreglo(int arreglo[TAM]) {
    for (int k = 0; k < TAM; k++) {
        printf("Arreglo[%d] = %d\n", k, arreglo[k]);
    }
}

void main() {
    puts("Bienvenido");
    int* arreglo = crearArreglo();
    puts("Arreglo original");
    imprimeArreglo(arreglo);
    ordenaSeleccion(arreglo);
    puts("Arreglo ordenado");
    imprimeArreglo(arreglo);
    destruirArreglo(arreglo);
    puts("Fin del programa");
}
