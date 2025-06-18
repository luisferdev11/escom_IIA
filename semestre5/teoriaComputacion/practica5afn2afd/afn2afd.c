#include "afn2afd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crear una lista vacía de estados AFD
ListaEstadosAFD *crearListaEstadosAFD(int capacidadInicial) {
    ListaEstadosAFD *lista = (ListaEstadosAFD *)malloc(sizeof(ListaEstadosAFD));
    if (!lista) {
        printf("Error de memoria al crear lista de estados AFD.\n");
        exit(1);
    }

    lista->estados = (EstadoAFD **)malloc(capacidadInicial * sizeof(EstadoAFD *));
    if (!lista->estados) {
        printf("Error de memoria al crear array de estados AFD.\n");
        free(lista);
        exit(1);
    }

    lista->numEstados = 0;
    lista->capacidad = capacidadInicial;

    return lista;
}

void liberarListaEstadosAFD(ListaEstadosAFD *lista) {
    if (!lista) return;

    for (int i = 0; i < lista->numEstados; i++) {
        liberarEstadoAFD(lista->estados[i]);
    }

    free(lista->estados);
    free(lista);
}

// Crear un nuevo estado para el AFD a partir de un conjunto de estados del AFN
EstadoAFD *crearEstadoAFD(ConjuntoEstados *conjunto, char *nombre, AFN *afnOriginal) {
    EstadoAFD *estado = (EstadoAFD *)malloc(sizeof(EstadoAFD));
    if (!estado) {
        printf("Error de memoria al crear estado AFD.\n");
        exit(1);
    }

    estado->estados = (int *)malloc(conjunto->numEstados * sizeof(int));
    if (!estado->estados) {
        printf("Error de memoria al crear array de estados en AFD.\n");
        free(estado);
        exit(1);
    }

    estado->numEstados = conjunto->numEstados;
    estado->esFinal = 0;  // Inicializar como no final

    // Copiar los estados del conjunto
    for (int i = 0; i < conjunto->numEstados; i++) {
        estado->estados[i] = conjunto->estados[i];
        // Verificar si alguno de los estados es final
        if (afnOriginal->finales[conjunto->estados[i]]) {
            estado->esFinal = 1;
        }
    }

    // Asignar nombre al estado
    estado->nombre = copia_cadena(nombre);

    return estado;
}

void liberarEstadoAFD(EstadoAFD *estado) {
    if (!estado) return;

    free(estado->estados);
    free(estado->nombre);
    free(estado);
}

// Agregar un estado a la lista de estados AFD
int agregarEstadoAFD(ListaEstadosAFD *lista, EstadoAFD *estado) {
    // Verificar si se necesita ampliar la lista
    if (lista->numEstados >= lista->capacidad) {
        int nuevaCapacidad = lista->capacidad * 2;
        EstadoAFD **nuevosEstados = (EstadoAFD **)realloc(lista->estados, nuevaCapacidad * sizeof(EstadoAFD *));
        if (!nuevosEstados) {
            printf("Error de memoria al redimensionar lista de estados AFD.\n");
            exit(1);
        }
        lista->estados = nuevosEstados;
        lista->capacidad = nuevaCapacidad;
    }

    // Agregar el estado a la lista
    lista->estados[lista->numEstados] = estado;
    lista->numEstados++;

    return lista->numEstados - 1;  // Índice del estado agregado
}

// Buscar un conjunto de estados en la lista de estados AFD
int buscarEstadoAFD(ListaEstadosAFD *lista, ConjuntoEstados *conjunto) {
    for (int i = 0; i < lista->numEstados; i++) {
        // Si tienen diferente número de estados, no son iguales
        if (lista->estados[i]->numEstados != conjunto->numEstados) {
            continue;
        }

        // Verificar si todos los estados del conjunto están en el estado AFD
        int encontrados = 0;
        for (int j = 0; j < conjunto->numEstados; j++) {
            int estadoEncontrado = 0;
            for (int k = 0; k < lista->estados[i]->numEstados; k++) {
                if (conjunto->estados[j] == lista->estados[i]->estados[k]) {
                    estadoEncontrado = 1;
                    break;
                }
            }
            if (estadoEncontrado) {
                encontrados++;
            }
        }

        // Si el número de estados encontrados coincide, son el mismo conjunto
        if (encontrados == conjunto->numEstados) {
            return i;
        }
    }

    return -1;  // No se encontró el conjunto
}

// Función para calcular el conjunto de estados alcanzables con un símbolo (mover)
ConjuntoEstados *mover(AFN *afn, ConjuntoEstados *estados, int simbolo) {
    ConjuntoEstados *resultado = crearConjuntoEstados(afn->numEstados);

    // Para cada estado en el conjunto
    for (int i = 0; i < estados->numEstados; i++) {
        int estadoActual = estados->estados[i];

        // Obtener transiciones con el símbolo dado
        NodoTransicion *trans = afn->transiciones[estadoActual][simbolo];

        // Agregar todos los estados destino al resultado
        while (trans) {
            agregarEstado(resultado, trans->destino);
            trans = trans->siguiente;
        }
    }

    return resultado;
}

// Crear una lista vacía de transiciones AFD
ListaTransicionesAFD *crearListaTransicionesAFD(int capacidadInicial) {
    ListaTransicionesAFD *lista = (ListaTransicionesAFD *)malloc(sizeof(ListaTransicionesAFD));
    if (!lista) {
        printf("Error de memoria al crear lista de transiciones AFD.\n");
        exit(1);
    }

    lista->transiciones = (TransicionAFD **)malloc(capacidadInicial * sizeof(TransicionAFD *));
    if (!lista->transiciones) {
        printf("Error de memoria al crear array de transiciones AFD.\n");
        free(lista);
        exit(1);
    }

    lista->numTransiciones = 0;
    lista->capacidad = capacidadInicial;

    return lista;
}

void liberarListaTransicionesAFD(ListaTransicionesAFD *lista) {
    if (!lista) return;

    for (int i = 0; i < lista->numTransiciones; i++) {
        free(lista->transiciones[i]->origen);
        free(lista->transiciones[i]->destino);
        free(lista->transiciones[i]);
    }

    free(lista->transiciones);
    free(lista);
}

// Agregar una transición a la lista de transiciones AFD
void agregarTransicionAFD(ListaTransicionesAFD *lista, char *origen, char *simbolo, char *destino) {
    // Verificar si se necesita ampliar la lista
    if (lista->numTransiciones >= lista->capacidad) {
        int nuevaCapacidad = lista->capacidad * 2;
        TransicionAFD **nuevasTransiciones = (TransicionAFD **)realloc(lista->transiciones,
                                                                       nuevaCapacidad * sizeof(TransicionAFD *));
        if (!nuevasTransiciones) {
            printf("Error de memoria al redimensionar lista de transiciones AFD.\n");
            exit(1);
        }
        lista->transiciones = nuevasTransiciones;
        lista->capacidad = nuevaCapacidad;
    }

    // Crear la nueva transición
    TransicionAFD *nuevaTransicion = (TransicionAFD *)malloc(sizeof(TransicionAFD));
    if (!nuevaTransicion) {
        printf("Error de memoria al crear transición AFD.\n");
        exit(1);
    }

    nuevaTransicion->origen = copia_cadena(origen);
    nuevaTransicion->simbolo[0] = simbolo[0];
    nuevaTransicion->simbolo[1] = '\0';
    nuevaTransicion->destino = copia_cadena(destino);

    // Agregar la transición a la lista
    lista->transiciones[lista->numTransiciones] = nuevaTransicion;
    lista->numTransiciones++;
}

// Buscar una transición en la lista de transiciones AFD
char *buscarTransicionAFD(ListaTransicionesAFD *lista, char *origen, char simbolo) {
    for (int i = 0; i < lista->numTransiciones; i++) {
        if (strcmp(lista->transiciones[i]->origen, origen) == 0 &&
            lista->transiciones[i]->simbolo[0] == simbolo) {
            return lista->transiciones[i]->destino;
        }
    }

    return NULL;  // No se encontró la transición
}

// Función para guardar el AFD en un archivo
void guardarAFD(ListaEstadosAFD *estadosAFD, ListaTransicionesAFD *transicionesAFD, AFN *afnOriginal, char *nombreArchivo) {
    FILE *f = fopen(nombreArchivo, "w");
    if (!f) {
        printf("Error al crear el archivo %s\n", nombreArchivo);
        return;
    }

    // Escribir los nombres de los estados
    for (int i = 0; i < estadosAFD->numEstados; i++) {
        fprintf(f, "%s", estadosAFD->estados[i]->nombre);
        if (i < estadosAFD->numEstados - 1) {
            fprintf(f, ",");
        }
    }
    fprintf(f, "\n");

    // Escribir el alfabeto (excluyendo epsilon)
    int primero = 1;
    for (int i = 0; i < afnOriginal->numSimbolos; i++) {
        if (!esEpsilon(afnOriginal, i)) {
            if (!primero) {
                fprintf(f, ",");
            }
            fprintf(f, "%s", afnOriginal->alfabeto[i]);
            primero = 0;
        }
    }
    fprintf(f, "\n");

    // Escribir el estado inicial (siempre es el primero, "A")
    fprintf(f, "%s\n", estadosAFD->estados[0]->nombre);

    // Escribir los estados finales
    primero = 1;
    for (int i = 0; i < estadosAFD->numEstados; i++) {
        if (estadosAFD->estados[i]->esFinal) {
            if (!primero) {
                fprintf(f, ",");
            }
            fprintf(f, "%s", estadosAFD->estados[i]->nombre);
            primero = 0;
        }
    }
    fprintf(f, "\n");

    // Escribir las transiciones
    for (int i = 0; i < transicionesAFD->numTransiciones; i++) {
        TransicionAFD *transicion = transicionesAFD->transiciones[i];
        fprintf(f, "%s,%s,%s\n",
                transicion->origen,
                transicion->simbolo,
                transicion->destino);
    }

    fclose(f);
    printf("AFD guardado en %s\n", nombreArchivo);
}

// Función para imprimir las equivalencias entre estados del AFD y estados del AFN
void imprimirEquivalenciasEstados(ListaEstadosAFD *estadosAFD, AFN *afnOriginal) {
    for (int i = 0; i < estadosAFD->numEstados; i++) {
        EstadoAFD *estado = estadosAFD->estados[i];

        printf("Estado %s = { ", estado->nombre);

        for (int j = 0; j < estado->numEstados; j++) {
            printf("%s", afnOriginal->estados[estado->estados[j]]);
            if (j < estado->numEstados - 1) {
                printf(", ");
            }
        }

        printf(" }\n");
    }
}

// Función para procesar una cadena en el AFD
int procesarCadenaAFD(ListaEstadosAFD *estadosAFD, ListaTransicionesAFD *transicionesAFD, char *estadoInicial, const char *cadena) {
    char *estadoActual = copia_cadena(estadoInicial);
    int len = longitud_cadena(cadena);

    // Si la cadena es vacía (lambda)
    if (len == 0) {
        // Verificar si el estado inicial es final
        for (int i = 0; i < estadosAFD->numEstados; i++) {
            if (strcmp(estadosAFD->estados[i]->nombre, estadoActual) == 0) {
                int esAceptada = estadosAFD->estados[i]->esFinal;
                free(estadoActual);
                return esAceptada;
            }
        }

        free(estadoActual);
        return 0;  // No es final, no se acepta
    }

    // Procesar cada símbolo de la cadena
    for (int i = 0; i < len; i++) {
        char simboloActual = cadena[i];

        // Buscar la transición para el estado actual y el símbolo actual
        char *estadoSiguiente = buscarTransicionAFD(transicionesAFD, estadoActual, simboloActual);

        // Si no hay transición, la cadena es rechazada
        if (!estadoSiguiente) {
            free(estadoActual);
            return 0;
        }

        // Actualizar el estado actual
        free(estadoActual);
        estadoActual = copia_cadena(estadoSiguiente);
    }

    // Verificar si el estado final es de aceptación
    for (int i = 0; i < estadosAFD->numEstados; i++) {
        if (strcmp(estadosAFD->estados[i]->nombre, estadoActual) == 0) {
            int esAceptada = estadosAFD->estados[i]->esFinal;
            free(estadoActual);
            return esAceptada;
        }
    }

    free(estadoActual);
    return 0;  // No se encontró el estado o no es final
}

// Función para convertir un AFN a un AFD
void convertirAFNaAFD(AFN *afn, ListaEstadosAFD **estadosAFD, ListaTransicionesAFD **transicionesAFD) {
    // Inicializar la lista de estados del AFD
    *estadosAFD = crearListaEstadosAFD(afn->numEstados);

    // Inicializar la lista de transiciones del AFD
    *transicionesAFD = crearListaTransicionesAFD(afn->numEstados * afn->numSimbolos);

    // Calcular la cerradura-ε del estado inicial del AFN
    ConjuntoEstados *estadoInicial = clausuraEpsilon(afn, afn->estadoInicial);

    // Crear el primer estado del AFD con la cerradura-ε del estado inicial
    char nombreInicial[2] = "A";
    EstadoAFD *estadoInicialAFD = crearEstadoAFD(estadoInicial, nombreInicial, afn);
    agregarEstadoAFD(*estadosAFD, estadoInicialAFD);

    // Lista de estados pendientes por procesar
    int estadosAgregados = 1;
    int estadosProcesados = 0;

    // Algoritmo de construcción de subconjuntos
    while (estadosProcesados < estadosAgregados) {
        EstadoAFD *estadoActual = (*estadosAFD)->estados[estadosProcesados];

        // Convertir el estado actual a un conjunto para hacer operaciones
        ConjuntoEstados *conjuntoActual = crearConjuntoEstados(estadoActual->numEstados);
        for (int i = 0; i < estadoActual->numEstados; i++) {
            agregarEstado(conjuntoActual, estadoActual->estados[i]);
        }

        // Para cada símbolo del alfabeto (excepto epsilon)
        for (int i = 0; i < afn->numSimbolos; i++) {
            // Ignorar epsilon
            if (esEpsilon(afn, i)) continue;

            // Calcular mover(T, a)
            ConjuntoEstados *movimiento = mover(afn, conjuntoActual, i);

            // Si el movimiento no es vacío
            if (movimiento->numEstados > 0) {
                // Calcular cerradura-ε(mover(T, a))
                ConjuntoEstados *nuevaClausura = clausuraEpsilonConjunto(afn, movimiento);

                // Verificar si este estado ya existe en el AFD
                int estadoExistente = buscarEstadoAFD(*estadosAFD, nuevaClausura);

                if (estadoExistente == -1) {
                    // Es un nuevo estado, crear y agregar al AFD
                    char nuevoNombre[2] = {(char)('A' + estadosAgregados), '\0'};
                    EstadoAFD *nuevoEstado = crearEstadoAFD(nuevaClausura, nuevoNombre, afn);
                    agregarEstadoAFD(*estadosAFD, nuevoEstado);

                    // Agregar transición del estado actual al nuevo estado
                    printf("Nueva transición: %s --%s--> %s\n",
                           estadoActual->nombre,
                           afn->alfabeto[i],
                           nuevoNombre);

                    // Guardar la transición
                    agregarTransicionAFD(*transicionesAFD,
                                         estadoActual->nombre,
                                         afn->alfabeto[i],
                                         nuevoNombre);

                    estadosAgregados++;
                } else {
                    // Ya existe, solo agregar transición
                    printf("Transición existente: %s --%s--> %s\n",
                           estadoActual->nombre,
                           afn->alfabeto[i],
                           (*estadosAFD)->estados[estadoExistente]->nombre);

                    // Guardar la transición
                    agregarTransicionAFD(*transicionesAFD,
                                         estadoActual->nombre,
                                         afn->alfabeto[i],
                                         (*estadosAFD)->estados[estadoExistente]->nombre);
                }

                liberarConjuntoEstados(nuevaClausura);
            }

            liberarConjuntoEstados(movimiento);
        }

        liberarConjuntoEstados(conjuntoActual);
        estadosProcesados++;
    }

    liberarConjuntoEstados(estadoInicial);
}