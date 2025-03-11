#include "set.h"

// Función hash djb2
uint32_t funcion_hash(char *clave) {
    uint32_t hash = 5381;
    int c;
    while ((c = *clave++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    return hash;
}

TablaHash *tabla_hash_crear(size_t capacidad) {
    TablaHash *tabla = (TablaHash *)malloc(sizeof(TablaHash));
    if (!tabla) {
        printf("Error de memoria al crear la tabla hash.\n");
        return NULL;
    }
    tabla->capacidad = capacidad;
    tabla->tam = 0;
    tabla->entradas = (EntradaHash *)calloc(capacidad, sizeof(EntradaHash));
    if (!tabla->entradas) {
        printf("Error de memoria al crear las entradas de la tabla hash.\n");
        free(tabla);
        return NULL;
    }
    return tabla;
}

int tabla_hash_insertar(TablaHash *tabla, char *clave) {
    if (!tabla || !clave) return 0;

    // Si la clave ya existe, imprimimos el duplicado
    if (tabla_hash_contiene(tabla, clave)) {
        printf("Elemento repetido detectado: \"%s\"\n", clave);
        return 0;
    }

    // Si se supera el factor de carga, redimensionar la tabla.
    if ((double)tabla->tam / tabla->capacidad >= FACTOR_CARGA) {
        tabla_hash_redimensionar(tabla);
    }

    uint32_t hash = funcion_hash(clave);
    size_t indice = hash % tabla->capacidad;

    // Sondeo lineal para insertar la clave
    for (size_t i = 0; i < tabla->capacidad; i++) {
        size_t pos = (indice + i) % tabla->capacidad;
        if (!tabla->entradas[pos].usado) {
            // Insertar la clave (haciendo una copia para evitar corrupción de memoria)
            tabla->entradas[pos].clave = copia_cadena(clave);
            tabla->entradas[pos].usado = 1;
            tabla->tam++;
            return 1;
        }
    }
    return 0;
}

void tabla_hash_redimensionar(TablaHash *tabla) {
    size_t nueva_capacidad = tabla->capacidad * 2;
    EntradaHash *nuevas_entradas = (EntradaHash *)calloc(nueva_capacidad, sizeof(EntradaHash));
    if (!nuevas_entradas) {
        printf("Error de memoria al redimensionar la tabla hash.\n");
        return;
    }
    // Guardar las entradas antiguas
    EntradaHash *antiguas_entradas = tabla->entradas;
    size_t antigua_capacidad = tabla->capacidad;

    tabla->entradas = nuevas_entradas;
    tabla->capacidad = nueva_capacidad;
    tabla->tam = 0;

    for (size_t i = 0; i < antigua_capacidad; i++) {
        if (antiguas_entradas[i].usado) {
            tabla_hash_insertar(tabla, antiguas_entradas[i].clave);
            free(antiguas_entradas[i].clave);
        }
    }
    free(antiguas_entradas);
}

int tabla_hash_contiene(TablaHash *tabla, char *clave) {
    if (!tabla || !clave) return 0;
    uint32_t hash = funcion_hash(clave);
    size_t indice = hash % tabla->capacidad;

    for (size_t i = 0; i < tabla->capacidad; i++) {
        size_t pos = (indice + i) % tabla->capacidad;
        if (tabla->entradas[pos].usado) {
            // Comparación manual de cadenas
            char *actual = tabla->entradas[pos].clave;
            int iguales = 1;
            int j = 0;
            while (actual[j] != '\0' && clave[j] != '\0') {
                if (actual[j] != clave[j]) {
                    iguales = 0;
                    break;
                }
                j++;
            }
            if (actual[j] != clave[j]) iguales = 0;
            if (iguales) return 1;
        } else {
            // Al encontrar una posición libre, se concluye que la clave no existe.
            return 0;
        }
    }
    return 0;
}

void tabla_hash_liberar(TablaHash *tabla) {
    if (!tabla) return;
    for (size_t i = 0; i < tabla->capacidad; i++) {
        if (tabla->entradas[i].usado) {
            free(tabla->entradas[i].clave);
        }
    }
    free(tabla->entradas);
    free(tabla);
}

void tabla_hash_imprimir(TablaHash *tabla) {
    if (!tabla) return;
    printf("{ ");
    for (size_t i = 0; i < tabla->capacidad; i++) {
        if (tabla->entradas[i].usado) {
            printf("\"%s\" ", tabla->entradas[i].clave);
        }
    }
    printf("}\n");
}
