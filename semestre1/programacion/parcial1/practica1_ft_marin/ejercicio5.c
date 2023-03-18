/*
Pseudocodigo:

Entrada: Real n1, n2, n3, n4, n5
Salida: Real n5, n4, n3, n2, n1

Imprimir "Escribe el primer número: "
Leer n1

Imprimir "Escribe el segundo número: "
Leer n2

Imprimir "Escribe el tercer número: "
Leer n3

Imprimir "Escribe el cuarto número: "
Leer n4

Imprimir "Escribe el quinto número: "
Leer n5

Imprimir "Orden inverso: " concatenar n5 concatenar ", " concatenar n4 concatenar ", "
concatenar n3 concatenar ", " concatenar n2 concatenar ", " concatenar n1
*/

#include <stdio.h>

int main() {
    float n1, n2, n3, n4, n5;

    printf("Escribe el primer número: ");
    scanf("%f", &n1);

    printf("Escribe el segundo número: ");
    scanf("%f", &n2);

    printf("Escribe el tercer número: ");
    scanf("%f", &n3);

    printf("Escribe el cuarto número: ");
    scanf("%f", &n4);

    printf("Escribe el quinto número: ");
    scanf("%f", &n5);

    printf("Orden inverso: %f, %f, %f, %f, %f \n", n5, n4, n3, n2, n1);
    return 0;
}
