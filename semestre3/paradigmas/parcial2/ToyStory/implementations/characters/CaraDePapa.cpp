#include "characters/CaraDePapa.h"
#include <stdio.h>

CaraDePapa::CaraDePapa() : Juguete("Cara de Papa") {}

void CaraDePapa::jugar() {
    printf("Cara de Papa juega!\n");
}

void CaraDePapa::romper() {
    printf("Cara de Papa se rompe en torilla!\n");
}

void CaraDePapa::marchitar() {
    printf("Cara de Papa se marchita siendo pepino!\n");
}

void CaraDePapa::crecer() {
    printf("Cara de Papa crece como una papa!\n");
}

void CaraDePapa::desarmar() {
    printf("Cara de Papa se desarma en sus piezas!\n");
}