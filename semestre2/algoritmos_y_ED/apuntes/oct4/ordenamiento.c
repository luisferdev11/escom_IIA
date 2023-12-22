#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1000

void mezcla(int* arregloIzq, int tamI, int* arregloDer, int tamD, int* arregloFinal);
void divide(int* arregloFinal, int tam);

int* crearArreglo(int tam) {
    int* arreglo = calloc(tam, sizeof(int));
    if (arreglo == NULL) {
        printf("No se pudo crear el arreglo");
        exit(1);
    }
    return arreglo;
}

// Todo lo que sea consulta, se pasa por valor y no referencia para no modificar los datos

void imprimeArreglo(int arreglo[], int tam) {
    for (int k = 0; k < tam; k++) {
        printf("Arreglo[%d] = %d\n", k, arreglo[k]);
    }
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

// mezcla

void divide(int* arregloFinal, int tam) {
    if (tam > 1) {
        int mitad = tam / 2;
        int* arregloIzq = crearArreglo(mitad);
        int* arregloDer = crearArreglo(tam - mitad);
        int i, j;

        for (i = 0; i < mitad; i++) {
            arregloIzq[i] = arregloFinal[i];
        }

        for (j = 0; j < tam - mitad; j++) {
            arregloDer[j] = arregloFinal[i];
            i++;
        }

        divide(arregloIzq, mitad);
        divide(arregloDer, tam - mitad);

        mezcla(arregloIzq, mitad, arregloDer, tam - mitad, arregloFinal);

        destruirArreglo(arregloIzq);
        destruirArreglo(arregloDer);
    }
}

void mezcla(int* arregloIzq, int tamI, int* arregloDer, int tamD, int* arregloFinal) {
    int i = 0, j = 0, k = 0;

    while (i < tamI && j < tamD) {
        if (arregloIzq[i] < arregloDer[j]) {
            arregloFinal[k] = arregloIzq[i];
            i++;
        } else {
            arregloFinal[k] = arregloDer[j];
            j++;
        }
        k++;
    }

    while (i < tamI) {
        arregloFinal[k] = arregloIzq[i];
        i++;
        k++;
    }

    while (j < tamD) {
        arregloFinal[k] = arregloDer[j];
        j++;
        k++;
    }
}

void main() {
    puts("Bienvenido");
    int nElementos = 15000000;
    int* arreglo = crearArreglo(nElementos);
    srand(time(NULL));
    for (int i = 0; i < nElementos; i++) {
        arreglo[i] = rand() % 20 - 1;
    }
    puts("Arreglo original");
    imprimeArreglo(arreglo, nElementos);
    divide(arreglo, nElementos);
    // ordenaSeleccion(arreglo);
    puts("Arreglo ordenado");
    imprimeArreglo(arreglo, nElementos);
    // destruirArreglo(arreglo);
    // puts("Fin del programa");
}