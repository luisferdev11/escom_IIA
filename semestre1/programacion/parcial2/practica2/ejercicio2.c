/*
Pseudocódigo:

Entrada: Entero hospitalization_time, age, disease
Salida: Flotante total_fee

Constantes: Entero DIABETES = 1500, HYPERTENSION = 1100, CANCER = 2200

Imprimir "Ingrese el tiempo de hospitalización en días: "
Leer hospitalization_time

Imprimir "Ingrese la edad del paciente: "
Leer age

Imprimir "Ingrese el tipo de enfermedad que tiene el paciente."
Imprimir "Presione 1 si se trata de diabetes."
Imprimir "Presione 2 si se trata de hipertensión."
Imprimir "Presione 3 si se trata de cáncer.\n"
Leer disease

Si (disease == 1) entonces
    total_fee = DIABETES
sino si (disease == 2) entonces
    total_fee = HYPERTENSION
sino si (disease == 3) entonces
    total_fee = CANCER
sino
    Imprimir "Valores no válidos"
    Terminar el programa
finSi

total_fee = total_fee * hospitalization_time

Si (age >= 12 y age <= 25) entonces
    total_fee = total_fee * 1.10
finSi

Imprimir "El costo total será de: " concatenar total_fee

*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    const int DIABETES = 1500, HYPERTENSION = 1100, CANCER = 2200;

    int age, hospitalization_time, disease;
    float total_fee;

    printf("Ingrese el tiempo de hospitalización en días: ");
    scanf("%d", &hospitalization_time);

    printf("Ingrese la edad del paciente: ");
    scanf("%d", &age);

    printf("Ingrese el tipo de enfermedad que tiene el pactiente.\nPresiona 1 si se trata de diabetes.\nPresiona 2 si se trata de hipertensión.\nPresiona 3 si se trata de cáncer.\n\n");
    scanf("%d", &disease);

    if (disease == 1) {
        total_fee = DIABETES;
    }
    if (disease == 2) {
        total_fee = HYPERTENSION;
    }
    if (disease == 3) {
        total_fee = CANCER;
    }
    if (disease != 1 && disease != 2 && disease != 3) {
        printf("Valores no válidos");
        exit(0);
    }

    total_fee = total_fee * hospitalization_time;

    if (age <= 25 && age >= 12) {
        total_fee = total_fee * 1.10;
    }

    printf("El costo total será de: %f\n", total_fee);

    return 0;
}
