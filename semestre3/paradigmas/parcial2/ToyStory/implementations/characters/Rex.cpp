#include "characters/Rex.h"
#include <stdio.h>

Rex::Rex() : Juguete("Rex") {}

void Rex::jugarVideojuegos() {
    printf("Rex juega videojuegos!\n");
}

void Rex::rugir() {
    printf("Rex ruge!\n");
}

void Rex::jugar() {
    printf("Rex juega!\n");
}

void Rex::vencer(Villano* villano) {
    printf("Rex vence al villano!\n");
}

