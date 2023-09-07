#include "Ejemplo.h"

int suma(int a, int b) {
    int resultado = a + b;
    return resultado;
}
// 16 bytes resultado, entrada a y b y variable global valor, cada dato entero mide 4 bytes
// 4 + 4 + 4 + 4 = 16 bytes

// 128 bits = 16 bytes

// tamaño de los tipos de datos en RAM en c
// int 4 bytes
// char 1 byte
// float 4 bytes 2 bytes parte entera y 2 bytes parte decimal
// Long 4 bytes se utiliza para cambiar
// short 2 bytes
// double 8 bytes 4 bytes parte entera y 4 bytes parte decimal

void main() {
    int a = 5;
    int b = 7;
    int resultado = suma(a, b);  // 24 bytes
    // 28 bytes
    printf("El resultado es: %d\n", resultado);
    printf("El valor es: %d\n", valor);
}