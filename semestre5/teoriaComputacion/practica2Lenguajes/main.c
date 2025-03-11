#include <stdio.h>
#include <stdlib.h>

#include "cadenas.h"
#include "lenguajes.h"
#include "set.h"

#define BUFFER_SIZE 201

// Función para leer una línea (incluyendo espacios) desde la entrada estándar.
void leer_cadena(char *buffer, int size) {
    fgets(buffer, size, stdin);
    // Eliminar el salto de línea final si existe.
    int i = 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
        i++;
    }
}

int main() {
    int cant1, cant2;
    char buffer[BUFFER_SIZE];

    printf("Operaciones con lenguajes (conjuntos de cadenas)\n");

    printf("Ingrese la cantidad de elementos para el lenguaje 1: ");
    scanf("%d", &cant1);
    getchar();  // Limpiar el salto de línea

    // Crear lenguaje 1 (se asigna una capacidad estimada)
    TablaHash *lenguaje1 = tabla_hash_crear(cant1 * 2);
    for (int i = 0; i < cant1; i++) {
        printf("Ingrese el elemento %d para el lenguaje 1: ", i + 1);
        leer_cadena(buffer, BUFFER_SIZE);
        tabla_hash_insertar(lenguaje1, buffer);
    }

    printf("Ingrese la cantidad de elementos para el lenguaje 2: ");
    scanf("%d", &cant2);
    getchar();  // Limpiar el salto de línea

    // Crear lenguaje 2
    TablaHash *lenguaje2 = tabla_hash_crear(cant2 * 2);
    for (int i = 0; i < cant2; i++) {
        printf("Ingrese el elemento %d para el lenguaje 2: ", i + 1);
        leer_cadena(buffer, BUFFER_SIZE);
        tabla_hash_insertar(lenguaje2, buffer);
    }

    int opcion;
    do {
        printf("\nMenú de operaciones:\n");
        printf("1. Unión de lenguajes\n");
        printf("2. Concatenación de lenguajes\n");
        printf("3. Potencia de un lenguaje\n");
        printf("Ingrese la opción (1-3): ");
        scanf("%d", &opcion);
        getchar();

        TablaHash *resultado = NULL;
        int subopcion;
        int potencia_valor;
        int lenguaje_sel;

        switch (opcion) {
            case 1:
                resultado = lenguaje_union(lenguaje1, lenguaje2);
                printf("Resultado de la unión:\n");
                tabla_hash_imprimir(resultado);
                printf("Tamaño: %zu\n", resultado->tam);
                break;
            case 2:
                printf("Seleccione la concatenación:\n");
                printf("1. L1 concatenado con L2\n");
                printf("2. L2 concatenado con L1\n");
                printf("Ingrese la opción (1 o 2): ");
                scanf("%d", &subopcion);
                getchar();
                if (subopcion == 1) {
                    resultado = lenguaje_concatenar(lenguaje1, lenguaje2);
                } else if (subopcion == 2) {
                    resultado = lenguaje_concatenar(lenguaje2, lenguaje1);
                } else {
                    printf("Opción inválida.\n");
                }
                if (resultado) {
                    printf("Resultado de la concatenación:\n");
                    tabla_hash_imprimir(resultado);
                    printf("Tamaño: %zu\n", resultado->tam);
                }
                break;
            case 3:
                printf("Seleccione el lenguaje para la potencia:\n");
                printf("1. Lenguaje 1\n");
                printf("2. Lenguaje 2\n");
                printf("Ingrese la opción (1 o 2): ");
                scanf("%d", &lenguaje_sel);
                getchar();
                printf("Ingrese el valor de la potencia (puede ser negativo): ");
                scanf("%d", &potencia_valor);
                getchar();
                if (lenguaje_sel == 1) {
                    resultado = lenguaje_potencia(lenguaje1, potencia_valor);
                } else if (lenguaje_sel == 2) {
                    resultado = lenguaje_potencia(lenguaje2, potencia_valor);
                } else {
                    printf("Opción inválida.\n");
                }
                if (resultado) {
                    printf("Resultado de la potencia:\n");
                    tabla_hash_imprimir(resultado);
                    printf("Tamaño: %zu\n", resultado->tam);
                }
                break;
            default:
                printf("Opción inválida.\n");
        }
        if (resultado) {
            tabla_hash_liberar(resultado);
        }
        int continuar;
        printf("¿Desea realizar otra operación? (1 = Sí, 0 = No): ");
        scanf("%d", &continuar);
        getchar();
        if (!continuar)
            break;
    } while (1);

    // Liberar la memoria de los lenguajes
    tabla_hash_liberar(lenguaje1);
    tabla_hash_liberar(lenguaje2);

    return 0;
}
