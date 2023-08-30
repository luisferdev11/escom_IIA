#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// #include <windows.h>

#define ROJO "\x1b[41m"
#define NEGRO "\x1b[40m"
#define RESET "\x1b[0m"

void imprimir(int n, int matriz[][n]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (matriz[i][j] == 1) {
                printf(ROJO "  " RESET);
            } else if (matriz[i][j] == 0) {
                printf(NEGRO "  " RESET);
            }
        }
        printf("\n");
    }
}

int main() {
    int n, i, j, x = 0, y = 0, opcion, aleatorio, instantes, re, inicio, num_cel;

    printf("Introduzca el tamano del tablero: ");
    scanf("%d", &n);

    n = abs(n);

    printf("\nIntroduzca el numero de instantes que quiera ver: ");
    scanf("%d", &instantes);
    instantes = abs(instantes);

    int matriz[n][n];
    int respaldo[n][n];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matriz[i][j] = 0;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }

        printf("\n");
    }
    printf("\n\npaso 1\n\n");
    printf("Escriba la opcion correspondiente para generar la configuracion inicial:\n1.-aleatorio\n2.- lo genera usted\n");
    scanf("%d", &opcion);
    if (opcion == 1) {
        srand(time(NULL));

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                aleatorio = rand() % 2;
                matriz[i][j] = aleatorio;
            }
        }

    } else if (opcion == 2) {
        printf("Introduzca el numero de celulas vivas que desea colocar (se recomiendan mas de 5): ");
        scanf("%d", &num_cel);
        for (int i = 0; i < num_cel; i++) {
            printf("Introduzca la coordenada de la celula viva %d (x,y): \ningrese los dos numeros separados por coma\n", i + 1);
            scanf("%d,%d", &x, &y);
            matriz[x][y] = 1;
        }
    }

    system("clear");
    // system("cls");

    printf("\n Estado inicial\n");
    imprimir(n, matriz);
    printf("\n");
    // printf("\n Presione 1 para iniciar\n");
    // scanf("%i", &inicio);

    while (inicio != 1) {
        printf("\n1.- Iniciar\n");
        printf("2.- Matar una célula\n");
        printf("3.- Resucitar una célula\n");
        printf("Ingrese una opción: ");
        scanf("%i", &inicio);

        if (inicio == 2) {
            printf("Introduzca la coordenada de la célula a matar (x,y): \nIngrese los dos números separados por coma\n");
            scanf("%d,%d", &x, &y);
            matriz[x][y] = 0;
        } else if (inicio == 3) {
            printf("Introduzca la coordenada de la célula a resucitar (x,y): \nIngrese los dos números separados por coma\n");
            scanf("%d,%d", &x, &y);
            matriz[x][y] = 1;
        }
        system("clear");
        imprimir(n, matriz);
    }

    system("clear");

    for (int l = 0; l < instantes; l++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                respaldo[i][j] = matriz[i][j];
            }
        }
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    re = (respaldo[i + 1][j] + respaldo[i][j + 1] + respaldo[i + 1][j + 1]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (i == n - 1 && j == 0) {
                    re = (respaldo[i - 1][j] + respaldo[i][j + 1] + respaldo[i - 1][j + 1]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (i == 0 && j == n - 1) {
                    re = (respaldo[i][j - 1] + respaldo[i + 1][j - 1] + respaldo[i + 1][j]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (i == n - 1 && j == n - 1) {
                    re = (respaldo[i - 1][j - 1] + respaldo[i][j - 1] + respaldo[i - 1][j]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (j == 0 && i != 0 && i != n - 1) {
                    re = (respaldo[i + 1][j] + respaldo[i][j + 1] + respaldo[i - 1][j] + respaldo[i + 1][j + 1] + respaldo[i - 1][j + 1]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2 || re > 3) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (i == 0 && j != 0 && j != n - 1) {
                    re = (respaldo[i + 1][j] + respaldo[i][j + 1] + respaldo[i][j - 1] + respaldo[i + 1][j + 1] + respaldo[i + 1][j - 1]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2 || re > 3) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (i == n - 1 && j != 0 && j != n - 1) {
                    re = (respaldo[i - 1][j] + respaldo[i][j + 1] + respaldo[i][j - 1] + respaldo[i - 1][j - 1] + respaldo[i - 1][j + 1]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2 || re > 3) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (j == n - 1 && i != 0 && i != n - 1) {
                    re = (respaldo[i + 1][j] + respaldo[i][j - 1] + respaldo[i - 1][j] + respaldo[i + 1][j - 1] + respaldo[i - 1][j - 1]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2 || re > 3) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
                if (i != 0 && j != 0 && i != n - 1 && j != n - 1) {
                    re = (respaldo[i + 1][j] + respaldo[i - 1][j] + respaldo[i - 1][j - 1] + respaldo[i + 1][j + 1] + respaldo[i - 1][j + 1] + respaldo[i + 1][j - 1] + respaldo[i][j - 1] + respaldo[i][j + 1]);
                    if (respaldo[i][j] == 1) {
                        if (re < 2 || re > 3) {
                            matriz[i][j] = 0;
                        }
                    } else {
                        if (re == 3)
                            matriz[i][j] = 1;
                    }
                }
            }
        }
        imprimir(n, matriz);
        printf("\n");
        if (instantes == 0) {
            usleep(2000000);
            // Sleep(2000);
        } else {
            usleep(195000);
            // Sleep(195);
        }

        system("clear");
        // system("cls");
    }
    printf("\n\n");

    return 0;
}