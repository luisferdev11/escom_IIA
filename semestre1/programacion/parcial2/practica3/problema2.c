#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n, resultado = 0;
    printf("Ingresa el primer valor entero: \n");
    scanf("%d", &m);
    printf("Ingresa el segundo valor entero: \n");
    scanf("%d", &n);

    for (int i = 0; i < abs(m); i++) {
        resultado += n;
    }

    if (m < 0) {
        resultado = -resultado;
    }

    printf("El resultado de la multiplicacion por sumas sucesivas es: %d\n", resultado);
    return 0;
}
