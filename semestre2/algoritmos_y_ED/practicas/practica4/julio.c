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

void ImprimePais(Pais* paises, int i) {
    printf("El Pais %s\n", paises[i].nombre);
    printf("Tiene: %ld habitantes\n", paises[i].poblacion);
    printf("Habla: %s\n", paises[i].idioma);
}

void OrdenarNombre(Pais* Paises, int tam) {
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

int main() {
    FILE* file;
    char line[MAX_LINE_LENGTH];
    char* token;
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
                if (token != NULL) {
                    strcpy(paises[paisCount].idioma, token);
                }
            }
        }

        paisCount++;
    }

    // Cierra el archivo
    fclose(file);

    // Imprime los datos almacenados para verificar
    // for (int i = 0; i < paisCount; i++) {
    //     printf("Pais: %s, Poblacion: %ld, Idioma: %s\n",
    //            paises[i].nombre, paises[i].poblacion, paises[i].idioma);
    // }

    OrdenarNombre(paises, 33);
    FILE* indicePais = fopen("IndicePais.txt", "r");
    FILE* Paises = fopen("Paises.txt", "r");
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
                printf("%d\n", i);
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
    return 0;
}