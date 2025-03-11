#ifndef SET_H
#define SET_H

#include "cadenas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FACTOR_CARGA 0.75

// Definición de la entrada de la tabla hash
typedef struct {
    char *clave;    // Clave (elemento del conjunto)
    uint8_t usado;  // 0: libre, 1: ocupado
} EntradaHash;

// Definición de la tabla hash
typedef struct {
    EntradaHash *entradas;
    size_t capacidad;
    size_t tam; // Número de elementos insertados
} TablaHash;

// Función hash (djb2)
uint32_t funcion_hash(char *clave);

// Crea una tabla hash con la capacidad indicada
TablaHash *tabla_hash_crear(size_t capacidad);

// Inserta una clave en la tabla hash; retorna 1 si se inserta, 0 si ya existe o hay error.
int tabla_hash_insertar(TablaHash *tabla, char *clave);

// Redimensiona la tabla hash cuando se supera el factor de carga.
void tabla_hash_redimensionar(TablaHash *tabla);

// Verifica si la tabla contiene la clave (retorna 1 si existe, 0 en caso contrario)
int tabla_hash_contiene(TablaHash *tabla, char *clave);

// Libera la memoria de la tabla hash.
void tabla_hash_liberar(TablaHash *tabla);

// Imprime el contenido de la tabla hash.
void tabla_hash_imprimir(TablaHash *tabla);

#endif // SET_H
