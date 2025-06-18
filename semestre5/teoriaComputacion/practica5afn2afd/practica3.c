#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automata.h"
#include "cadenas.h"

// Función para verificar si una cadena es aceptada por el AFN
void procesarCadena(AFN *afn, const char *cadena) {
    int len = longitud_cadena(cadena);
    
    // Si la cadena es vacía (lambda)
    if (len == 0) {
        // Verificar si el estado inicial es final o si hay un camino de epsilon a un estado final
        if (afn->finales[afn->estadoInicial]) {
            printf("La cadena vacía es aceptada.\n");
            return;
        } else if (afn->tieneEpsilon) {
            // Calcular la clausura epsilon del estado inicial
            ConjuntoEstados *clausura = clausuraEpsilon(afn, afn->estadoInicial);
            
            // Verificar si algún estado en la clausura es final
            int aceptada = 0;
            for (int i = 0; i < clausura->numEstados; i++) {
                if (afn->finales[clausura->estados[i]]) {
                    aceptada = 1;
                    break;
                }
            }
            
            liberarConjuntoEstados(clausura);
            
            if (aceptada) {
                printf("La cadena vacía es aceptada por transiciones epsilon.\n");
                return;
            }
        }
        
        printf("La cadena vacía es rechazada.\n");
        return;
    }
    
    // Preparar arreglos para el recorrido
    int *camino = (int *)malloc((len * 2 + 1) * sizeof(int));  // Espacio extra para posibles transiciones epsilon
    char *caminoSimbolos = (char *)malloc((len * 2 + 1) * sizeof(char));
    NodoRecorrido *listaRecorridos = NULL;
    
    if (!camino || !caminoSimbolos) {
        printf("Error de memoria al preparar el recorrido.\n");
        free(camino);
        free(caminoSimbolos);
        exit(1);
    }
    
    // Buscar caminos de aceptación
    dfs(afn, afn->estadoInicial, cadena, 0, len, camino, caminoSimbolos, 0, &listaRecorridos);
    
    // Mostrar resultados
    if (listaRecorridos) {
        printf("Cadena '%s' aceptada.\n", cadena);
        imprimirRecorridosConNombres(afn, listaRecorridos);
    } else {
        printf("Cadena '%s' rechazada.\n", cadena);
    }
    
    // Liberar memoria
    while (listaRecorridos) {
        NodoRecorrido *temp = listaRecorridos;
        listaRecorridos = listaRecorridos->siguiente;
        free(temp->estados);
        free(temp->simbolos);
        free(temp);
    }
    free(camino);
    free(caminoSimbolos);
}

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

    // Mostrar información del autómata
    printf("=== Automata Finito No Determinista ===\n");
    imprimirAFN(afn);
    printf("======================================\n\n");

    // Ciclo de procesamiento de cadenas
    char buffer[256];
    printf("Ingresa la cadena (o 'salir' para terminar): ");
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
        
        // Procesar la cadena
        procesarCadena(afn, buffer);
        
        // Pedir otra cadena
        printf("\nIngresa la cadena (o 'salir' para terminar): ");
    }

    // Liberar recursos
    liberarAFN(afn);
    return 0;
}
