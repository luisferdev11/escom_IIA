#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_PAISES 100

typedef struct {
    char nombre[50];
    long poblacion;
    char idioma[50];
} Pais;

void ImprimePais(Pais *paises, int i) {
    printf("El Pais %s \n", paises[i].nombre);
    printf("Tiene: %ld  habitantes\n", paises[i].poblacion);
    printf("Habla: %s \n", paises[i].idioma);
}

void OrdenarNombre(Pais *Paises, int tam) {
    int i, j;
    Pais Auxiliar;
    for (i = 0; i < tam - 1; i++) {
        for (j = i + 1; j < tam; j++) {
            int comparacion = strcmp(Paises[i].nombre, Paises[j].nombre);
            if (comparacion > 0) {
                Auxiliar = Paises[i];
                Paises[i] = Paises[j];
                Paises[j] = Auxiliar;
            }
        }
    }
}

void ordenaSeleccionPoblacion(Pais *paises, int n) {
    int max_idx;
    for (int i = 0; i < n - 1; i++) {
        max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (paises[j].poblacion > paises[max_idx].poblacion) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            // Intercambia paises[i] y paises[max_idx]
            Pais temp = paises[i];
            paises[i] = paises[max_idx];
            paises[max_idx] = temp;
        }
    }
}

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Pais paises[MAX_PAISES];
    int paisCount = 0;

    // Abre el archivo CSV
    file = fopen("datos.csv", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Lee cada línea del archivo
    while (fgets(line, MAX_LINE_LENGTH, file) && paisCount < MAX_PAISES) {
        token = strtok(line, ",");
        if (token != NULL) {
            strcpy(paises[paisCount].nombre, token);

            token = strtok(NULL, ",");
            if (token != NULL) {
                paises[paisCount].poblacion = atol(token);

                token = strtok(NULL, ",");
                token[strcspn(token, "\n")] = 0;
                if (token != NULL) {
                    strcpy(paises[paisCount].idioma, token);
                }
            }
        }

        paisCount++;
    }

    // Cierra el archivo
    fclose(file);

    int opcion;
    do {
        printf("Menu de opciones:\n");
        printf("1. Buscar mi país de origen (placeholder)\n");
        printf("2. Buscar países por idioma (placeholder)\n");
        printf("3. Mostrar la cantidad total de población que habla un idioma\n");
        printf("4. Mostrar países en orden descendente por población\n");
        printf("5. Salir\n");
        printf("Ingresa tu opción: ");
        scanf("%d", &opcion);

        char idiomaBuscado[50];

        switch (opcion) {
            case 1:
                // Placeholder para la opción 1
                OrdenarNombre(paises, 33);
                FILE *indicePais = fopen("IndicePais.txt", "r");
                FILE *Paises = fopen("Paises.txt", "r");
                if (indicePais == NULL || Paises == NULL) {
                    printf("Archivos no disponibles\n");
                    exit(1);
                }
                int indice, indicePaises = 1;
                int posLineaPaisesInicial;
                int posLineaPaisesLimiteSup;
                int arregloIndices[255];
                char Paise[35][100];
                char linea[4] = {'\0'};
                char valor[3] = {'\0'};
                int exito = 0;
                char elementoBuscado[100];
                printf("Ingrese el Pais a buscar: ");
                scanf("%s", elementoBuscado);
                int tamano = strlen(elementoBuscado);
                elementoBuscado[tamano] = '\n';
                printf("%s", elementoBuscado);
                while (!feof(indicePais)) {
                    fgets(linea, 4, indicePais);
                    for (indice = 0; indice < strlen(linea); indice++) {
                        valor[indice] = linea[indice + 1];
                    }
                    arregloIndices[(int)linea[0]] = atoi(valor);
                }
                while (!feof(Paises)) {
                    fgets(Paise[indicePaises], 100, Paises);
                    indicePaises++;
                }
                int i = (int)elementoBuscado[0];
                if (i > 0) {
                    posLineaPaisesInicial = arregloIndices[i];
                    while (arregloIndices[i + 1] == 0) {
                        i++;
                    }
                    posLineaPaisesLimiteSup = arregloIndices[i + 1];
                    for (i = posLineaPaisesInicial; i < posLineaPaisesLimiteSup; i++) {
                        printf("Comparando %s vs %s\n", elementoBuscado, Paise[i]);
                        if (strcmp(elementoBuscado, Paise[i]) == 0) {
                            ImprimePais(paises, i);
                            exito = 1;
                            break;
                        }
                    }
                } else {
                    exito = 0;
                }
                (exito) ? puts("Se encontro el elemento") : puts("No se encontro el elemento");
                fclose(indicePais);
                fclose(Paises);
                break;
            case 2:
                // Placeholder para la opción 2

                printf("Ingresa el idioma para calcular la población total: ");
                scanf("%s", idiomaBuscado);

                // Busqueda secuenciaGOD
                for (int i = 0; i < paisCount; i++) {
                    if (strcmp(paises[i].idioma, idiomaBuscado) == 0) {
                        printf("Pais: %s, Poblacion: %ld, Idioma: %s\n",
                               paises[i].nombre, paises[i].poblacion, paises[i].idioma);
                    }
                }

                break;
            case 3:
                // Pillo inciso 3

                printf("Ingresa el idioma para calcular la población total: ");
                scanf("%s", idiomaBuscado);

                long totalPoblacion = 0;

                // Busqueda secuenciaGOD
                for (int i = 0; i < paisCount; i++) {
                    if (strcmp(paises[i].idioma, idiomaBuscado) == 0) {
                        totalPoblacion += paises[i].poblacion;
                    }
                }

                printf("Población total que habla %s: %ld\n", idiomaBuscado, totalPoblacion);
                break;
            case 4:
                // Pillo inciso 4

                ordenaSeleccionPoblacion(paises, paisCount);

                // Imprime los países ordenados
                printf("Paises ordenados por poblacion en orden descendente:\n");
                for (int i = 0; i < paisCount; i++) {
                    printf("Pais: %s, Poblacion: %ld, Idioma: %s\n",
                           paises[i].nombre, paises[i].poblacion, paises[i].idioma);
                }

                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}
