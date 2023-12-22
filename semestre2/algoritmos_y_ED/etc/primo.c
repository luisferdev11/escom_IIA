/* Contenido de primo.c */
#include "primo.h"

#include <math.h>

int primo(int numero) {
    int i;
    for (i = 2; i <= sqrt(numero); i++) {
        if (numero % i == 0) {
            return 0;
        }
    }
    return 1;
}