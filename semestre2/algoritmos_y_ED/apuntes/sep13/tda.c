#include "tda.h"

Llanta crearLlanta(float precio, float radio, char marca[50]) {
    Llanta llantaNueva;
    llantaNueva.precio = precio;
    llantaNueva.radio = radio;
    strcpy(llantaNueva.marca, marca);

    return llantaNueva;
};

Carro crearCarro(Llanta llantas[4], char marca[30], int fab) {
    Carro miCoche;
    for (int i = 0; i < 4; i++)
        miCoche.llantas[i] = llantas[i];

    strcpy(miCoche.marca, marca);
    miCoche.aFabricacion = fab;

    return miCoche;
};

void consultarCarro(Carro carro) {
    puts("Imprimiendo datos de mi coche:");
    printf("Marca: %s\n", carro.marca);
    printf("Año de fabricacion: %d\n", carro.aFabricacion);
    printf("Llantas:\n");
    for (int i = 0; i < 4; i++) {
        printf("Datos de la llanta #%u\n", i);
        consultarLlanta(carro.llantas[i]);
    }
};

void consultarLlanta(Llanta llanta) {
    printf("Marca: %s\n", llanta.marca);
    printf("Precio: %1.2f\n", llanta.precio);
    printf("Radio: %1.2f\n", llanta.radio);
};

void main() {
    puts("Comenzando programa...");
    Llanta miaLlantas[4];
    for (int i = 0; i < 4; i++) {
        miaLlantas[i] = crearLlanta(1000.0, 255, "Michelin");
    }
    puts("Llantas creadas...");

    Carro miCarro = crearCarro(miaLlantas, "Ferrari", 2020);

    consultarCarro(miCarro);

    puts("Fin de programa...");
}