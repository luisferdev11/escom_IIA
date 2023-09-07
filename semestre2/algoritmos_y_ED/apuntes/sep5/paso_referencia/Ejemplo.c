#include "Ejemplo.h"

int suma(int* a, int* b) {
    return (*a) + (*b);
}

void main() {
    int a = 5;
    int b = 7;
    int resultado = suma(&a, &b);  // &a --> direccion de aS
    printf("El resultado es: %d\n", resultado);

    // 16 bytes 4 global, 4 a, 4 b y 4 resultado
}