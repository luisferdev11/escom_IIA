#include "pelota.h"

#include <stdio.h>
#include <stdlib.h>

void crearPelota(struct Pelota **p, int *n) {
    (*n)++;
    *p = realloc(*p, (*n) * sizeof(struct Pelota));
    printf("Alto: ");
    scanf("%d", &(*p)[*n - 1].alto);
    printf("Ancho: ");
    scanf("%d", &(*p)[*n - 1].ancho);
    printf("Color: ");
    scanf("%s", (*p)[*n - 1].color);
}

void destruirPelota(struct Pelota **p, int *n, int index) {
    if (index < 0 || index >= *n) {
        printf("Índice no válido.\n");
        return;
    }
    for (int i = index; i < *n - 1; i++) {
        (*p)[i] = (*p)[i + 1];
    }
    (*n)--;
    *p = realloc(*p, (*n) * sizeof(struct Pelota));
}

void leerPelotas(struct Pelota *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("Pelota %d:\n", i + 1);
        printf("Alto: %d\n", p[i].alto);
        printf("Ancho: %d\n", p[i].ancho);
        printf("Color: %s\n", p[i].color);
    }
}

void menuOperaciones(struct Pelota **p, int *n) {
    int opcion;
    int index;
    do {
        printf("1. Crear pelota\n");
        printf("2. Destruir pelota\n");
        printf("3. Leer pelotas\n");
        printf("4. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                crearPelota(p, n);
                break;
            case 2:
                printf("Índice de la pelota a destruir: ");
                scanf("%d", &index);
                destruirPelota(p, n, index - 1);
                break;
            case 3:
                leerPelotas(*p, *n);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
                break;
        }
    } while (opcion != 4);
}
