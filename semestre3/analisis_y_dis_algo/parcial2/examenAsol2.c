#include <stdio.h>

// Función para imprimir espacios.
void imprimir_espacios(int cuenta) {
    if (cuenta > 0) {
        printf(" ");
        imprimir_espacios(cuenta - 1);
    }
}

// Función para imprimir una línea del rombo con espacios y estrellas.
void imprimir_linea(int espacios, int estrellas) {
    if (estrellas == 1) {
        imprimir_espacios(espacios);
        printf("*\n");  // Imprime una estrella y un salto de línea
    } else if (estrellas > 1) {
        imprimir_espacios(espacios);
        printf("*");
        imprimir_espacios(estrellas - 2);  // Calcula el espacio entre estrellas
        printf("*\n");
    }
}

// Función recursiva para imprimir la parte superior e inferior del rombo.
void imprimir_rombo(int actual, int total) {
    if (actual > total) return;  // Caso base: si actual excede el total, termina la recursión.

    // Calcula los espacios necesarios para centrar las estrellas.
    int espacios = (total - actual) / 2;

    // Imprime la parte superior del rombo.
    imprimir_linea(espacios, actual);

    // Llamada recursiva para la siguiente línea del rombo.
    imprimir_rombo(actual + 2, total);

    // Imprime la parte inferior del rombo solo si estamos en la fase de retorno y no en la línea central.
    if (actual != total) imprimir_linea(espacios, actual);
}

int main() {
    int tamaño;
    printf("Ingrese el tamaño del rombo (número impar): ");
    scanf("%d", &tamaño);
    imprimir_rombo(1, tamaño);  // Comienza desde la línea más estrecha (1 estrella).
    return 0;
}
