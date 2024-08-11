#include <stdio.h>

void cambio_monedas_ilimitadas(int cantidad, int index, int denominaciones[], int cantidad_monedas[]) {
    if (index >= 4 || cantidad == 0) {
        return;
    }

    cantidad_monedas[index] = cantidad / denominaciones[index];
    cambio_monedas_ilimitadas(cantidad % denominaciones[index], index + 1, denominaciones, cantidad_monedas);
}

int main() {
    int cantidad;
    int denominaciones[] = {20, 10, 5, 1};
    int cantidad_monedas[4] = {0};

    printf("Ingrese la cantidad de cambio: ");
    scanf("%d", &cantidad);

    cambio_monedas_ilimitadas(cantidad, 0, denominaciones, cantidad_monedas);

    printf("Cambio con monedas ilimitadas:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d monedas de %d\n", cantidad_monedas[i], denominaciones[i]);
    }

        return 0;
}
