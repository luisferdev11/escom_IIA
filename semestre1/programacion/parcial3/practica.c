#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 12
#define ASIENTOS 6
#define MITAD 3

void inicializar_asientos(int asientos[FILAS][ASIENTOS]) {
    srand(time(NULL));
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < ASIENTOS; j++)
            asientos[i][j] = rand() % 2;
}

void imprimir_asientos(int asientos[FILAS][ASIENTOS]) {
    printf("mapa de los asientos:\n 1-ocupado\n 2-desocupado \n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < ASIENTOS; j++) {
            if (j == MITAD) printf("\t--");
            printf("\t%d", asientos[i][j]);
        }
        printf("\n");
    }
}

int obtener_numero(const char* prompt, int max) {
    int num;
    do {
        printf("\n%s \n>> ", prompt);
        scanf("%d", &num);
    } while (num <= 0 || num > max);
    return num - 1;
}

void mostrar_menu_principal() {
    printf("\n----- Bienvenido a la aerolínea -----");
    printf("\n1. Reservar asiento");
    printf("\n2. Cancelar asiento");
    printf("\n3. Salir");
    printf("\n-------------------------------------");
    printf("\n>> ");
}

void gestionar_asiento(int asientos[FILAS][ASIENTOS], int reserva) {
    int fila = obtener_numero("Ingresa el número de fila donde está el asiento.", FILAS);
    int asiento = obtener_numero("Ingresa el número de asiento.", ASIENTOS);

    if (asientos[fila][asiento] == reserva) {
        printf("\nNo puedes %s este asiento ya que %s.\n",
               reserva ? "reservar" : "cancelar",
               reserva ? "se encuentra ocupado" : "no se encuentra reservado aún");
    } else {
        asientos[fila][asiento] = reserva;
        printf("\nAsiento #%d %s correctamente en la fila #%d.\n",
               asiento + 1,
               reserva ? "reservado" : "cancelado",
               fila + 1);
    }
}

int main() {
    int asientos[FILAS][ASIENTOS];
    inicializar_asientos(asientos);
    imprimir_asientos(asientos);

    while (1) {
        int opcion;
        mostrar_menu_principal();
        scanf("%d", &opcion);

        if (opcion == 3) break;
        gestionar_asiento(asientos, opcion == 1 ? 1 : 0);
        imprimir_asientos(asientos);
    }

    return 0;
}
