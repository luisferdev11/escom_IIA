#include "lenguajes.h"

#include "cadenas.h"

// Unión: inserta en un nuevo conjunto todos los elementos de ambos lenguajes.
TablaHash *lenguaje_union(TablaHash *lenguaje1, TablaHash *lenguaje2) {
    size_t capacidad = lenguaje1->capacidad + lenguaje2->capacidad;
    TablaHash *resultado = tabla_hash_crear(capacidad);
    for (size_t i = 0; i < lenguaje1->capacidad; i++) {
        if (lenguaje1->entradas[i].usado) {
            tabla_hash_insertar(resultado, lenguaje1->entradas[i].clave);
        }
    }
    for (size_t i = 0; i < lenguaje2->capacidad; i++) {
        if (lenguaje2->entradas[i].usado) {
            tabla_hash_insertar(resultado, lenguaje2->entradas[i].clave);
        }
    }
    return resultado;
}

// Concatenación: para cada elemento de lenguaje1 se concatena con cada elemento de lenguaje2.
TablaHash *lenguaje_concatenar(TablaHash *lenguaje1, TablaHash *lenguaje2) {
    size_t capacidad = lenguaje1->tam * lenguaje2->tam;
    if (capacidad < 10) capacidad = 10;
    TablaHash *resultado = tabla_hash_crear(capacidad);
    for (size_t i = 0; i < lenguaje1->capacidad; i++) {
        if (lenguaje1->entradas[i].usado) {
            for (size_t j = 0; j < lenguaje2->capacidad; j++) {
                if (lenguaje2->entradas[j].usado) {
                    char *concatenado = concatenar(lenguaje1->entradas[i].clave, lenguaje2->entradas[j].clave);
                    tabla_hash_insertar(resultado, concatenado);
                    free(concatenado);
                }
            }
        }
    }
    return resultado;
}

// Inversión: devuelve un lenguaje con cada cadena invertida.
TablaHash *lenguaje_invertir(TablaHash *lenguaje) {
    TablaHash *resultado = tabla_hash_crear(lenguaje->capacidad);
    for (size_t i = 0; i < lenguaje->capacidad; i++) {
        if (lenguaje->entradas[i].usado) {
            char *invertida = invertir_cadena(lenguaje->entradas[i].clave);
            tabla_hash_insertar(resultado, invertida);
            free(invertida);
        }
    }
    return resultado;
}

// Función auxiliar para clonar un lenguaje
static TablaHash *clonar_lenguaje(TablaHash *lenguaje) {
    TablaHash *clon = tabla_hash_crear(lenguaje->capacidad);
    for (size_t i = 0; i < lenguaje->capacidad; i++) {
        if (lenguaje->entradas[i].usado) {
            tabla_hash_insertar(clon, lenguaje->entradas[i].clave);
        }
    }
    return clon;
}

// Potencia: para n>=0, se define L^0 = {""}, L^1 = L y para n>1 se usa exponentiation by squaring.
// Si n es negativo se invierten las cadenas y se opera con el valor absoluto.
TablaHash *lenguaje_potencia(TablaHash *lenguaje, int n) {
    if (n < 0) {
        TablaHash *invertido = lenguaje_invertir(lenguaje);
        TablaHash *resultado = lenguaje_potencia(invertido, -n);
        tabla_hash_liberar(invertido);
        return resultado;
    }
    if (n == 0) {
        TablaHash *resultado = tabla_hash_crear(10);
        tabla_hash_insertar(resultado, "");
        return resultado;
    }
    if (n == 1) {
        return clonar_lenguaje(lenguaje);
    }
    if (n % 2 == 0) {
        TablaHash *half = lenguaje_potencia(lenguaje, n / 2);
        TablaHash *resultado = lenguaje_concatenar(half, half);
        tabla_hash_liberar(half);
        return resultado;
    } else {
        TablaHash *temp = lenguaje_potencia(lenguaje, n - 1);
        TablaHash *resultado = lenguaje_concatenar(lenguaje, temp);
        tabla_hash_liberar(temp);
        return resultado;
    }
}
