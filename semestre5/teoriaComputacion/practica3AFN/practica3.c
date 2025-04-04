#include <stdio.h>
#include <stdlib.h>

#include "automata.h"
#include "cadenas.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo_automata.txt>\n", argv[0]);
        return 1;
    }

    AFN *afn = cargarAFN(argv[1]);
    if (!afn) {
        printf("Error al cargar el autómata.\n");
        return 1;
    }

    // Imprimir datos del autómata
    printf("Estado inicial: %s\n", afn->estados[afn->estadoInicial]);
    printf("Estados posibles: ");
    for (int i = 0; i < afn->numEstados; i++) {
        printf("%s", afn->estados[i]);
        if (i < afn->numEstados - 1)
            printf(", ");
    }
    printf("\nEstados finales: ");
    int primero = 1;
    for (int i = 0; i < afn->numEstados; i++) {
        if (afn->finales[i]) {
            if (!primero)
                printf(", ");
            printf("%s", afn->estados[i]);
            primero = 0;
        }
    }
    printf("\nAlfabeto: ");
    for (int i = 0; i < afn->numSimbolos; i++) {
        printf("%s", afn->alfabeto[i]);
        if (i < afn->numSimbolos - 1)
            printf(", ");
    }
    printf("\n");

    // Ciclo de entrada
    char buffer[256];
    printf("Ingresa la cadena: ");
    while (fgets(buffer, sizeof(buffer), stdin)) {
        int len = longitud_cadena(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        if (len == 0)
            continue;
        // Si se ingresa "salir", terminar
        if (longitud_cadena(buffer) == 5 &&
            buffer[0] == 's' && buffer[1] == 'a' && buffer[2] == 'l' && buffer[3] == 'i' && buffer[4] == 'r')
            break;

        // Preparar arreglo para almacenar el recorrido y los símbolos consumidos
        int *camino = (int *)malloc((len + 1) * sizeof(int));
        char *caminoSimbolos = (char *)malloc((len + 1) * sizeof(char));  // Para (len) transiciones, terminador incluido
        NodoRecorrido *listaRecorridos = NULL;

        dfs(afn, afn->estadoInicial, buffer, 0, len, camino, caminoSimbolos, 0, &listaRecorridos);

        if (listaRecorridos)
            imprimirRecorridosConNombres(afn, listaRecorridos);
        else
            printf("Cadena '%s' rechazada.\n", buffer);

        // Liberar la lista de recorridos
        while (listaRecorridos) {
            NodoRecorrido *temp = listaRecorridos;
            listaRecorridos = listaRecorridos->siguiente;
            free(temp->estados);
            free(temp->simbolos);
            free(temp);
        }
        free(camino);
        free(caminoSimbolos);

        printf("Ingresa la cadena: ");
    }

    liberarAFN(afn);
    return 0;
}
