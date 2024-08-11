#include <stdio.h>

void cambio_monedas_limitadas(int cantidad, int index, int denominaciones[], int cantidad_monedas[], int monedas[]) {
    if (index >= 4 || cantidad == 0) {
        return;
    }

    int num_monedas = (cantidad / denominaciones[index] <= monedas[index]) ? (cantidad / denominaciones[index]) : monedas[index];
    cantidad_monedas[index] = num_monedas;
    cambio_monedas_limitadas(cantidad - num_monedas * denominaciones[index], index + 1, denominaciones, cantidad_monedas, monedas);
}

int main() {
    int cantidad;
    int denominaciones[] = {50, 20, 10, 5};
    int cantidad_monedas[4] = {0};
    int monedas[4];

    printf("Ingrese la cantidad de cambio: ");
    scanf("%d", &cantidad);

    printf("Ingrese la cantidad de monedas disponibles de 50, 20, 10 y 5 respectivamente: ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &monedas[i]);
    }

    cambio_monedas_limitadas(cantidad, 0, denominaciones, cantidad_monedas, monedas);

    printf("Cambio con monedas limitadas:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d monedas de %d\n", cantidad_monedas[i], denominaciones[i]);
    }

    // faltante
    if (cantidad_monedas[0] * denominaciones[0] + cantidad_monedas[1] * denominaciones[1] + cantidad_monedas[2] * denominaciones[2] + cantidad_monedas[3] * denominaciones[3] < cantidad) {
        printf("No se puede dar el cambio exacto\n");
        printf("Faltante: %d\n", cantidad - (cantidad_monedas[0] * denominaciones[0] + cantidad_monedas[1] * denominaciones[1] + cantidad_monedas[2] * denominaciones[2] + cantidad_monedas[3] * denominaciones[3]));
    }

    return 0;
}
