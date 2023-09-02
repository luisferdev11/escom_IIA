/*
    Luis Fernando Rodriguez Dominguez
    2BV2
    Ingenieria en Inteligencia Artificial
    30/08/2022
*/

/*
    Problema:
    Definir una estructura "Pelota" con los siguientes atributos:
        Dimensiones (alto, ancho)
        Color

    Crear las siguientes operaciones:
        Crear pelota (con memoria dinamica)
        Destruir pelota (liberar memoria dinamica)
        Leer pelota (visualizar datos en pantalla)
        MenuOperaciones (3 opciones para el usuario)

    Se almacenan con memoria dinamica las pelotas creadas y se leen todas
    las pelotas creadas.

    Gestionar el programa con 3 archivos: un .h con prototipos de
    funciones y dos .c (uno para el main y el otro con la
    implementación de los prototipos)
*/

#include <stdio.h>
#include <stdlib.h>

#include "pelota.h"

int main(int argc, char const *argv[]) {
    struct Pelota *misPelotas = NULL;
    int numPelotas = 0;
    menuOperaciones(&misPelotas, &numPelotas);
    free(misPelotas);
    return 0;
}
