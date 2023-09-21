/* Estructuras y Uniones */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// abstraer es la extraccion de las caracteristicas generales de un objeto

typedef struct {
    char caracter;
    int valor;
} Dato;

typedef union {
    char caracter;
    int valor;
} Data;

// Arreglo dinamico
int main(int argc, char const* argv[]) {
    Dato estructura;
    Data uniones;
    estructura.valor = 64;
    uniones.valor = 64;

    printf("Datos de la estructura: %d\n; caracter %c\n", estructura.valor, estructura.caracter);
    printf("Datos de la union: %d\n; caracter %c\n", uniones.valor, uniones.caracter);
}