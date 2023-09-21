#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    float precio;
    float radio;
    char marca [50];
} Llanta;

typedef struct
{
    Llanta llantas[4];
    char marca [30];
    int aFabricacion;
} Carro;

Llanta crearLlanta(float, float, char[50]);

Carro crearCarro(Llanta[4], char[30], int);

void consultarCarro(Carro);

void consultarLlanta(Llanta);