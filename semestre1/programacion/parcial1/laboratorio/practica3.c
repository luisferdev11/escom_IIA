/*
Pseudocódigo:

Entrada: Real sueldo_base = 8000, venta
Salida: Real sueldo_bruto, sueldo_neto, comision, impuestos

Imprimir "Hola, ingresa la ganancia en las ventas que has obtenido: "
Leer venta

Si venta < 0 Entonces
    Imprimir "Valor incorrecto"
SiNo
    Si venta > 0 y venta < 6000 Entonces
        comision = 0.20 * venta
    FinSi
    Si venta >= 6000 Entonces
        comision = 0.30 * venta
    FinSi

    sueldo_bruto = sueldo_base + comision

    Si sueldo_bruto <= 9000 Entonces
        impuestos = 0.05 * sueldo_bruto
    SiNo
        impuestos = 0.08 * sueldo_bruto
    FinSi

    sueldo_neto = sueldo_bruto - impuestos

    Imprimir "El sueldo bruto es de: " concatenar sueldo_bruto
    Imprimir "Pagas de impuestos: " concatenar impuestos
    Imprimir "Tu sueldo será de " concatenar sueldo_neto
FinSi


*/
#include <stdio.h>
int main() {
    const float sueldo_base = 8000;
    float sueldo_bruto, sueldo_neto, venta, comision, impuestos;

    printf("Hola, ingresa la ganancia en las ventas que has obtenido: ");
    scanf("%f", &venta);

    if (venta < 0) {
        printf("Valor incorrecto\n");
    } else {
        if (venta > 0 && venta <= 6000) {
            comision = 0.20 * venta;
        }
        if (venta > 6000) {
            comision = 0.30 * venta;
        }

        sueldo_bruto = sueldo_base + comision;

        if (sueldo_bruto <= 9000) {
            impuestos = 0.05 * sueldo_bruto;
        } else {
            impuestos = .08 * sueldo_bruto;
        }

        sueldo_neto = sueldo_bruto - impuestos;

        printf("El sueldo bruto es de: %f\n", sueldo_bruto);
        printf("Pagas de impuestos: %f\n", impuestos);

        printf("Tu sueldo será de %f\n", sueldo_neto);
    }

    return 0;
}
