#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 0.0
#define SUP 20000.0
#define MESES 12

void mostrarVentas(double ventas[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Ventas del mes %d: %.2f\n", i + 1, ventas[i]);
    }
}

double calcularTotal(double ventas[], int size) {
    double total = 0.0;
    for (int i = 0; i < size; i++) {
        total += ventas[i];
    }
    return total;
}

double calcularPromedio(double ventas[], int size) {
    double total = calcularTotal(ventas, size);
    return total / size;
}

int mesMayorVenta(double ventas[], int size) {
    int mes = 0;
    for (int i = 1; i < size; i++) {
        if (ventas[i] > ventas[mes]) {
            mes = i;
        }
    }
    return mes + 1;
}

int main() {
    double ventas[MESES];
    srand(time(NULL));  // Semilla para la generación de números aleatorios

    // Generar las ventas
    for (int i = 0; i < MESES; i++) {
        ventas[i] = INF + rand() * (SUP - INF) / RAND_MAX;
    }

    mostrarVentas(ventas, MESES);

    double total = calcularTotal(ventas, MESES);
    printf("El total de ventas del año es: %.2f\n", total);

    double promedio = calcularPromedio(ventas, MESES);
    printf("El promedio de ventas por mes es: %.2f\n", promedio);

    int mes = mesMayorVenta(ventas, MESES);
    printf("El mes con la mayor venta fue: %d con una venta de %.2f\n", mes, ventas[mes - 1]);

    return 0;
}