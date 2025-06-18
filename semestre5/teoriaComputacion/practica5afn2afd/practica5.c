#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afn2afd.h"
#include "automata.h"
#include "cadenas.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo_automata.txt>\n", argv[0]);
        return 1;
    }

    // Cargar el AFN desde el archivo
    AFN *afn = cargarAFN(argv[1]);
    if (!afn) {
        printf("Error al cargar el autómata.\n");
        return 1;
    }

    // Mostrar información del autómata original
    printf("=== Automata Finito No Determinista Original ===\n");
    imprimirAFN(afn);
    printf("============================================\n\n");

    // Inicializar estructuras para el AFD
    ListaEstadosAFD *estadosAFD = NULL;
    ListaTransicionesAFD *transicionesAFD = NULL;

    // Convertir AFN a AFD
    convertirAFNaAFD(afn, &estadosAFD, &transicionesAFD);

    // Mostrar las equivalencias entre los estados del AFD y los del AFN
    printf("\n=== Equivalencias de Estados ===\n");
    imprimirEquivalenciasEstados(estadosAFD, afn);

    // Guardar el AFD resultante
    guardarAFD(estadosAFD, transicionesAFD, afn, "afd_resultado.txt");

    // Ciclo de procesamiento de cadenas
    char buffer[256];
    printf("\nIngresa la cadena (o 'salir' para terminar): ");
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Eliminar el salto de línea del final
        int len = longitud_cadena(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        // Verificar si quiere salir
        if (len == 5 && strcmp(buffer, "salir") == 0)
            break;

        // Procesar la cadena en el AFD
        int resultado = procesarCadenaAFD(estadosAFD, transicionesAFD, "A", buffer);

        if (resultado) {
            printf("Cadena '%s' aceptada por el AFD.\n", buffer);
        } else {
            printf("Cadena '%s' rechazada por el AFD.\n", buffer);
        }

        // Pedir otra cadena
        printf("\nIngresa la cadena (o 'salir' para terminar): ");
    }

    // Liberar memoria
    liberarListaEstadosAFD(estadosAFD);
    liberarListaTransicionesAFD(transicionesAFD);
    liberarAFN(afn);

    return 0;
}