/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
6-oct-2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float alto;
    float ancho;
    char titulo[100];
    char fuente[100];
} Libro;

int compararPorAltoAsc(Libro *a, Libro *b) {
    return (a->alto > b->alto) - (a->alto < b->alto);
}

int compararPorAltoDesc(Libro *a, Libro *b) {
    return compararPorAltoAsc(b, a);
}

int compararPorAnchoAsc(Libro *a, Libro *b) {
    return (a->ancho > b->ancho) - (a->ancho < b->ancho);
}

int compararPorAnchoDesc(Libro *a, Libro *b) {
    return compararPorAnchoAsc(b, a);
}

int compararPorTituloAsc(Libro *a, Libro *b) {
    return strcmp(a->titulo, b->titulo);
}

int compararPorTituloDesc(Libro *a, Libro *b) {
    return compararPorTituloAsc(b, a);
}

int compararPorFuenteAsc(Libro *a, Libro *b) {
    return strcmp(a->fuente, b->fuente);
}

int compararPorFuenteDesc(Libro *a, Libro *b) {
    return compararPorFuenteAsc(b, a);
}

void ordenaSeleccion(Libro *libros, int count, int (*comparar)(Libro *, Libro *)) {
    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (comparar(&libros[j], &libros[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Libro temp = libros[i];
            libros[i] = libros[min_idx];
            libros[min_idx] = temp;
        }
    }
}

int main() {
    FILE *file = fopen("/home/pillofon/Documents/escom/semestre2/algoritmos_y_ED/practicas/practica3/BD_Libros.csv", "r");
    if (!file) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    Libro libros[30];
    int count = 0;
    char line[500];

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%*d,\"%[^\"]\",%f,%f,\"%[^\"]\"", libros[count].titulo, &libros[count].alto, &libros[count].ancho, libros[count].fuente);
        count++;
    }

    fclose(file);

    // imprimir todos los libros
    for (int i = 0; i < count; i++) {
        printf("%s (%.2f x %.2f, %s)\n", libros[i].titulo, libros[i].alto, libros[i].ancho, libros[i].fuente);
    }

    int opcion,
        orden;
    while (1) {
        printf("Elija el atributo de orden:\n");
        printf("1. Dimensiones (alto)\n");
        printf("2. Título de la página\n");
        printf("3. Dimensiones (ancho)\n");
        printf("4. Tipo de fuente\n");
        printf("5. Salir\n");
        scanf("%d", &opcion);

        if (opcion == 5) {
            break;
        }

        printf("Elija el orden:\n");
        printf("1. Ascendente\n");
        printf("2. Descendente\n");
        scanf("%d", &orden);

        switch (opcion) {
            case 1:
                ordenaSeleccion(libros, count, orden == 1 ? compararPorAltoAsc : compararPorAltoDesc);
                break;
            case 2:
                ordenaSeleccion(libros, count, orden == 1 ? compararPorTituloAsc : compararPorTituloDesc);
                break;
            case 3:
                ordenaSeleccion(libros, count, orden == 1 ? compararPorAnchoAsc : compararPorAnchoDesc);
                break;
            case 4:
                ordenaSeleccion(libros, count, orden == 1 ? compararPorFuenteAsc : compararPorFuenteDesc);
                break;
        }

        for (int i = 0; i < count; i++) {
            printf("%s (%.2f x %.2f, %s)\n", libros[i].titulo, libros[i].alto, libros[i].ancho, libros[i].fuente);
        }
    }

    return 0;
}
