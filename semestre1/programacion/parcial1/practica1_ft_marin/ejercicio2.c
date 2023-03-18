/*
Pseudocodigo:

Entrada: Real a, b, c, d, e, f
Salida: Real x, y,

Imprimir "Escribe el coeficiente a: "
Leer a

Imprimir "Escribe el coeficiente b: "
Leer b

Imprimir "Escribe el resultado de la primera ecuación (c): "
Leer c

Imprimir "Escribe el coeficiente d: "
Leer d

Imprimir "Escribe el coeficiente e: "
Leer e

Imprimir "Escribe el resultado de la segunda ecuación (f): "
Leer f

Si ((a * e) - (b * d) == 0) entonces
    Imprimir "La ecuación dada no tiene soluciones"
sino
    x = ((c * e) - (b * f)) / ((a * e) - (b * d))
    y = ((a * f) - (c * d)) / ((a * e) - (b * d))
    Imprimir "El valor de x es: " concatenar x
    Imprimir "El valor de y es: " concatenar y
finSi

*/

#include <stdio.h>

int main() {
    float x, y;
    float a, b, c, d, e, f;

    printf("Escribe el coeficiente a: ");
    scanf("%f", &a);

    printf("Escribe el coeficiente b: ");
    scanf("%f", &b);

    printf("Escribe el resultado de la primera ecuación (c): ");
    scanf("%f", &c);

    printf("Escribe el coeficiente d: ");
    scanf("%f", &d);

    printf("Escribe el coeficiente e: ");
    scanf("%f", &e);

    printf("Escribe el resultado de la segunda ecuación (f): ");
    scanf("%f", &f);

    if ((a * e) - (b * d) == 0) {
        printf("La ecuación dada no tiene soluciones \n");
    } else {
        x = ((c * e) - (b * f)) / ((a * e) - (b * d));

        y = ((a * f) - (c * d)) / ((a * e) - (b * d));

        printf("El valor de x es: %f \n", x);
        printf("El valor de y es: %f \n", y);
    }

    return 0;
}
