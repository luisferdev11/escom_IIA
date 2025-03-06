#include <stdio.h>
#include <stdlib.h>

#include "cadenas.h"

int main() {
    char entrada[201];
    printf("Ingrese una cadena (máximo 200 caracteres): ");
    scanf("%[^\n]", entrada);

    int opcion;
    do {
        printf("\nMenú:\n");
        printf("1. Operador de prefijo y sufijo\n");
        printf("2. Subcadena\n");
        printf("3. Subsecuencia\n");
        printf("4. Potencia (inversa y potencia)\n");
        printf("Ingrese la tarea a realizar (1-4): ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int n;
                printf("Ingrese n: ");
                scanf("%d", &n);
                imprimir_prefijo_sufijo(entrada, n);
                break;
            }
            case 2: {
                int n, m;
                printf("Ingrese n (cantidad de caracteres a quitar del inicio): ");
                scanf("%d", &n);
                printf("Ingrese m (cantidad de caracteres a quitar del final): ");
                scanf("%d", &m);
                char *sub = obtener_subcadena(entrada, n, m);
                if (sub) {
                    printf("Subcadena: %s\n", sub);
                    free(sub);
                }
                break;
            }
            case 3: {
                int count;
                printf("Ingrese la cantidad de posiciones a remover: ");
                scanf("%d", &count);
                int *posiciones = (int *)malloc(count * sizeof(int));
                if (!posiciones) {
                    printf("Error de memoria.\n");
                    break;
                }
                for (int i = 0; i < count; i++) {
                    printf("Ingrese la posición %d (1-indexado): ", i + 1);
                    scanf("%d", &posiciones[i]);
                }
                char *subsec = remover_subsecuencia(entrada, posiciones, count);
                if (subsec) {
                    printf("Subsecuencia: %s\n", subsec);
                    free(subsec);
                }
                free(posiciones);
                break;
            }
            case 4: {
                int pot;
                printf("Ingrese n (la potencia): ");
                scanf("%d", &pot);
                if (pot <= 0) {
                    /* Para esta opción se invierte la cadena y se potencia */
                    char *resultado = potencia_inversa(entrada, pot * -1);
                    if (resultado) {
                        printf("Resultado de la potencia inversa: %s\n", resultado);
                        free(resultado);
                    } else {
                        printf("Error en la operación.\n");
                    }
                    break;
                } else {
                    char *resultado = potencia(entrada, pot);
                    if (resultado) {
                        printf("Resultado de la potencia: %s\n", resultado);
                        free(resultado);
                    } else {
                        printf("Error en la operación.\n");
                    }
                    break;
                }
            }
            default:
                printf("Opción inválida.\n");
        }
        int continuar;
        printf("Desea realizar otra tarea con la misma cadena? (1 = Sí, 0 = No): ");
        scanf("%d", &continuar);
        if (!continuar)
            break;
    } while (1);

    return 0;
}

/* IMPLEMENTACIÓN DE LAS FUNCIONES */

/* Retorna la longitud de la cadena */
int longitud_cadena(const char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

/* Imprime el prefijo y sufijo de n caracteres de la cadena s */
void imprimir_prefijo_sufijo(const char *s, int n) {
    int len = longitud_cadena(s);
    if (n > len) {
        printf("Error: n mayor que la longitud de la cadena.\n");
        return;
    }
    printf("Prefijo: ");
    for (int i = 0; i < n; i++) {
        printf("%c", s[i]);
    }
    printf("\nSufijo: ");
    for (int i = len - n; i < len; i++) {
        printf("%c", s[i]);
    }
    printf("\n");
}

/* Retorna una nueva cadena que es el prefijo de n caracteres de s */
char *obtener_prefijo(const char *s, int n) {
    int len = longitud_cadena(s);
    if (n > len) {
        printf("Error: n mayor que la longitud de la cadena.\n");
        return NULL;
    }
    char *prefijo = (char *)malloc((n + 1) * sizeof(char));
    if (!prefijo) {
        printf("Error de memoria.\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        prefijo[i] = s[i];
    }
    prefijo[n] = '\0';
    return prefijo;
}

/* Retorna una nueva cadena que es el sufijo de n caracteres de s */
char *obtener_sufijo(const char *s, int n) {
    int len = longitud_cadena(s);
    if (n > len) {
        printf("Error: n mayor que la longitud de la cadena.\n");
        return NULL;
    }
    char *sufijo = (char *)malloc((n + 1) * sizeof(char));
    if (!sufijo) {
        printf("Error de memoria.\n");
        return NULL;
    }
    int inicio = len - n;
    for (int i = 0; i < n; i++) {
        sufijo[i] = s[inicio + i];
    }
    sufijo[n] = '\0';
    return sufijo;
}

/* Retorna una nueva cadena que es la subcadena resultante de remover n caracteres del inicio y m del final */
char *obtener_subcadena(const char *s, int n, int m) {
    int len = longitud_cadena(s);
    if (n > len || m > len || (n + m) > len) {
        printf("Error: Los valores de n y m son inválidos para la cadena.\n");
        return NULL;
    }
    int nueva_long = len - n - m;
    if (nueva_long <= 0) {
        char *lambda = (char *)malloc(7 * sizeof(char));
        if (!lambda) return NULL;
        lambda[0] = 'l';
        lambda[1] = 'a';
        lambda[2] = 'm';
        lambda[3] = 'b';
        lambda[4] = 'd';
        lambda[5] = 'a';
        lambda[6] = '\0';
        return lambda;
    }
    /* Reutilizamos obtener_prefijo sobre la subcadena que inicia en s+n */
    char *subcadena = obtener_prefijo(s + n, nueva_long);
    return subcadena;
}

char *remover_subsecuencia(const char *s, int posiciones[], int count) {
    int len = longitud_cadena(s);
    int *marcas = (int *)malloc(len * sizeof(int));
    if (!marcas) {
        printf("Error de memoria.\n");
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        marcas[i] = 0;
    }
    for (int i = 0; i < count; i++) {
        int pos = posiciones[i];
        if (pos < 0 || pos >= len) {
            printf("Error: Posición %d fuera de rango.\n", posiciones[i]);
            free(marcas);
            return NULL;
        }
        marcas[pos] = 1;
    }
    char *resultado = (char *)malloc((len + 1) * sizeof(char));
    if (!resultado) {
        printf("Error de memoria.\n");
        free(marcas);
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (!marcas[i]) {
            resultado[j++] = s[i];
        }
    }
    resultado[j] = '\0';
    free(marcas);
    if (j == 0) {
        char *lambda = (char *)malloc(7 * sizeof(char));
        if (!lambda) return NULL;
        lambda[0] = 'l';
        lambda[1] = 'a';
        lambda[2] = 'm';
        lambda[3] = 'b';
        lambda[4] = 'd';
        lambda[5] = 'a';
        lambda[6] = '\0';
        free(resultado);
        return lambda;
    }
    return resultado;
}

char *invertir_cadena(const char *s) {
    int len = longitud_cadena(s);
    char *invertida = (char *)malloc((len + 1) * sizeof(char));
    if (!invertida) return NULL;
    for (int i = 0; i < len; i++) {
        invertida[i] = s[len - 1 - i];
    }
    invertida[len] = '\0';
    return invertida;
}

char *concatenar(const char *s1, const char *s2) {
    int len1 = longitud_cadena(s1);
    int len2 = longitud_cadena(s2);
    int total = len1 + len2;
    char *resultado = (char *)malloc((total + 1) * sizeof(char));
    if (!resultado) return NULL;
    int i = 0;
    for (int j = 0; j < len1; j++, i++) {
        resultado[i] = s1[j];
    }
    for (int j = 0; j < len2; j++, i++) {
        resultado[i] = s2[j];
    }
    resultado[total] = '\0';
    return resultado;
}

char *potencia(const char *s, int pot) {
    if (pot <= 0) {
        char *lambda = (char *)malloc(7 * sizeof(char));
        if (!lambda) return NULL;
        lambda[0] = 'l';
        lambda[1] = 'a';
        lambda[2] = 'm';
        lambda[3] = 'b';
        lambda[4] = 'd';
        lambda[5] = 'a';
        lambda[6] = '\0';
        return lambda;
    }
    int len = longitud_cadena(s);
    int total = len * pot;
    char *resultado = (char *)malloc((total + 1) * sizeof(char));
    if (!resultado) return NULL;
    for (int i = 0; i < pot; i++) {
        for (int j = 0; j < len; j++) {
            resultado[i * len + j] = s[j];
        }
    }
    resultado[total] = '\0';
    return resultado;
}

char *potencia_inversa(const char *s, int pot) {
    char *invertida = invertir_cadena(s);
    if (!invertida) return NULL;
    char *resultado = potencia(invertida, pot);
    free(invertida);
    return resultado;
}
