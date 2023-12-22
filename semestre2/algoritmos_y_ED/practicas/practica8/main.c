#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arboles.h"
#include "pila.h"

int main() {
    int n, i, choice;
    char input[100];
    char expression[100];
    Arbol miArbol = NULL;
    Dato dato;

    printf("Ingrese la cantidad de expresiones (entre 1 y 18): ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &n);

    if (n < 1 || n > 18) {
        printf("Número de expresiones fuera del rango permitido.\n");
        return 1;
    }

    srand(time(NULL));

    for (i = 0; i < n; i++) {
        printf("Ingrese la expresion posfija %d: ", i + 1);
        fgets(expression, sizeof(expression), stdin);
        expression[strcspn(expression, "\n")] = 0;

        dato.valor = rand() % 15 + 1;
        strcpy(dato.expresion, expression);
        insertarNodoArbol(&miArbol, dato);
    }
    while (choice != 1 && choice != 2 && choice != 3) {
        printf("Elija el orden de evaluación de las expresiones:\n");
        printf("1. Orden Ascendente\n");
        printf("2. Pre-Orden\n");
        printf("3. Pos-Orden\n");
        printf("Ingrese su elección: ");
        scanf("%d", &choice);

        // Limpieza del buffer de entrada
        while (getchar() != '\n')
            ;

        switch (choice) {
            case 1:
                printf("Evaluación en Orden Ascendente:\n");
                inOrden(miArbol, 1);  // Se pasa el nivel inicial como 1
                break;
            case 2:
                printf("Evaluación en Pre-Orden:\n");
                preOrden(miArbol, 1);  // Se pasa el nivel inicial como 1
                break;
            case 3:
                printf("Evaluación en Pos-Orden:\n");
                posOrden(miArbol, 1);  // Se pasa el nivel inicial como 1
                break;
            default:
                printf("Opción no válida.\n");
        }

        // Liberar el árbol al final
        eliminarArbol(&miArbol);
    }

    return 0;
}
