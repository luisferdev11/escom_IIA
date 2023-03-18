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
