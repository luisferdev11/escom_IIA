/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
20-sep-2023
*/

#include <stdio.h>

#include "futbolista.h"

int main() {
    Futbolista *futbolista1 = crearFutbolista("Lionel Messi", "Delantero", 30, "Paris Saint-Germain", 10, 2);

    if (futbolista1 == NULL) {
        printf("Fallo en la asignación de memoria.\n");
        return 1;
    }

    printf("Futbolista 1:\n");
    imprimirFutbolista(*futbolista1);

    Futbolista *futbolista2 = crearFutbolista("", "", 0, "", 0, 0);

    if (futbolista2 == NULL) {
        printf("Fallo en la asignación de memoria.\n");
        return 1;
    }

    copiarFutbolista(futbolista2, *futbolista1);

    printf("Futbolista 2 (copiado):\n");
    imprimirFutbolista(*futbolista2);

    // Destruir los Futbolistas
    destruirFutbolista(futbolista1);

    puts("Futbolista 1 destruido.");
    imprimirFutbolista(*futbolista1);

    puts("Futbolista 2 sin destruir.");
    imprimirFutbolista(*futbolista2);

    return 0;
}
