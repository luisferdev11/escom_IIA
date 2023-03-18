/*
Pseudocodigo:

Entrada: Entero seg
Salida: Entero seg, min, hr

Imprimir "Escribe el numero de segundos a convertir: "
Leer seg

hr = seg / 3600
seg = seg % 3600

min = seg / 60
seg = seg % 60

Imprimir "Horas: " concatenar hr
Imprimir "Minutos: " concatenar min
Imprimir "Segundos: " concatenar seg


*/

#include <stdio.h>

int main() {
    int seg, min, hr;

    printf("Escribe el numero de segundos a convertir: ");
    scanf("%d", &seg);

    hr = seg / 3600;
    seg = seg % 3600;

    min = seg / 60;
    seg = seg % 60;

    printf("Horas: %d \n", hr);
    printf("Minutos: %d \n", min);
    printf("Segundos: %d \n", seg);

    return 0;
}
