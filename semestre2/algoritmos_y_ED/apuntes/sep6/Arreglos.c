#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// version estatico:
// void imprimeArreglo(int* arreglo, int tam) {
//     // for (int i = 0; i < tam; i++) {
//     //     printf("%d\n", arreglo[i]);
//     // }

//     int pos = 0;
//     while (pos < tam) {
//         printf("%d\n", arreglo[pos]);
//         pos++;
//     }
// }

// int main(int argc, char** argv) {
//     int arregloA[10] = {40};       // se va a la memoria global
//     imprimeArreglo(arregloA, 10);  // siempre se apunta a la posiocion 0 de un arreglo
//     puts("Se terminó el programa");
// }

// version dinamica:

void imprimeArreglo(int* arreglo, int tam) {
    // for (int i = 0; i < tam; i++) {
    //     printf("%d\n", arreglo[i]);
    // }

    int pos = 0;
    while (pos < tam) {
        printf("%d\n", *(arreglo + pos));

        // aritmetica de apuntadores
        //  op 1 - op artimetica apuntador
        //  arreglo[0] - *arreglo  (porque siempre apunta a la posicion 0)
        //  arreglo[1] - *(arreglo + 1)

        pos++;
    }
}

void main(int argc, char** argv) {
    puts("Se inició el programa");
    int tam = 0, valor = 0;
    int agregaOtro = 0;  // Bandera si es 1 se agrega otro valor, si es 0 se termina el programa
    printf("Dame el tamaño del arreglo: ");
    scanf("%d", &tam);

    int* arreglo = malloc(tam * sizeof(int));  // se va a la memoria dinamica

    if (arreglo == NULL) {
        puts("No se pudo reservar memoria");
        exit(1);
    }

    for (int i = 0; i < tam; i++) {
        puts("Ingresa un valor: ");
        scanf("%d", &valor);
        arreglo[i] = valor;
    }

    while (1) {
        puts("Estos son los valores ingresados, ¿quieres agregar más?, si es asi, ingresa 1, si no, ingresa 0");
        imprimeArreglo(arreglo, tam);
        scanf("%d", &agregaOtro);
        switch (agregaOtro) {
            case 1:
                tam++;
                arreglo = realloc(arreglo, (tam) * sizeof(int));

                if (arreglo == NULL) {
                    puts("No se pudo reservar memoria");
                    exit(1);
                }

                puts("Ingresa un valor: ");
                scanf("%d", &valor);
                arreglo[tam - 1] = valor;

                break;
            case 0:
                free(arreglo);
                exit(0);
                break;
            default:
                puts("Opción no válida");
                break;
        }
    }

    free(arreglo);

    puts("Se termina el programa");
}
