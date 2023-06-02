#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LANZAMIENTOS 3000

int main() {
    int frecuencia[6] = {0};  // Inicializamos el arreglo de frecuencias a 0
    srand(time(NULL));        // Inicializamos la semilla para el generador de números aleatorios

    for (int i = 0; i < NUM_LANZAMIENTOS; i++) {
        int resultado = rand() % 6;  // Generamos un número aleatorio entre 0 y 5
        frecuencia[resultado]++;     // Incrementamos la frecuencia correspondiente
    }

    printf("Resultados después de %d lanzamientos:\n", NUM_LANZAMIENTOS);
    for (int i = 0; i < 6; i++) {
        double porcentaje = (double)frecuencia[i] / NUM_LANZAMIENTOS * 100;
        printf("Cara %d: %d lanzamientos (%.2f%%)\n", i + 1, frecuencia[i], porcentaje);
    }

    return 0;
}
