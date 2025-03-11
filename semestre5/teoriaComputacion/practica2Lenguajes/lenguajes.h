#ifndef LENGUAJES_H
#define LENGUAJES_H

#include "set.h"
#include <stdio.h>
#include <stdlib.h>

// Operaciones sobre lenguajes (conjuntos de cadenas)
TablaHash *lenguaje_union(TablaHash *lenguaje1, TablaHash *lenguaje2);
TablaHash *lenguaje_concatenar(TablaHash *lenguaje1, TablaHash *lenguaje2);
TablaHash *lenguaje_invertir(TablaHash *lenguaje);
TablaHash *lenguaje_potencia(TablaHash *lenguaje, int n);

#endif // LENGUAJES_H
