#include "cadenas.h"

int longitud_cadena(const char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

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

char *obtener_subcadena(const char *s, int n, int m) {
    int len = longitud_cadena(s);
    if (n > len || m > len || (n + m) > len) {
        printf("Error: Los valores de n y m son inválidos para la cadena.\n");
        return NULL;
    }
    int nueva_long = len - n - m;
    if (nueva_long <= 0) {
        char *lambda = copia_cadena(LAMBDA);
        return lambda;
    }
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
        int pos = posiciones[i] - 1;
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
        char *lambda = copia_cadena(LAMBDA);
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
        char *lambda = copia_cadena(LAMBDA);
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

char *copia_cadena(const char *s) {
    int len = longitud_cadena(s);
    char *copia = (char *)malloc((len + 1) * sizeof(char));
    if (!copia) return NULL;
    for (int i = 0; i <= len; i++) {
        copia[i] = s[i];
    }
    return copia;
}

// Función para dividir una cadena por un delimitador
char **dividir_cadena(const char *cadena, char delimitador, int *contador) {
    int tokens = 0, i = 0;
    // Contar tokens ignorando delimitadores consecutivos
    while (cadena[i] != '\0') {
        while (cadena[i] == delimitador && cadena[i] != '\0')
            i++;
        if (cadena[i] == '\0')
            break;
        tokens++;
        while (cadena[i] != delimitador && cadena[i] != '\0')
            i++;
    }
    char **resultado = (char **)malloc(tokens * sizeof(char *));
    int indice = 0;
    i = 0;
    while (cadena[i] != '\0') {
        while (cadena[i] == delimitador && cadena[i] != '\0')
            i++;
        if (cadena[i] == '\0')
            break;
        int inicio = i;
        while (cadena[i] != delimitador && cadena[i] != '\0')
            i++;
        int long_token = i - inicio;
        char *token = (char *)malloc((long_token + 1) * sizeof(char));
        for (int j = 0; j < long_token; j++) {
            token[j] = cadena[inicio + j];
        }
        token[long_token] = '\0';
        resultado[indice++] = token;
    }
    *contador = tokens;
    return resultado;
}

char *trim_cadena(const char *s) {
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
        s++;

    int len = longitud_cadena(s);
    if (len == 0)
        return copia_cadena("");

    const char *fin = s + len - 1;
    while (fin > s && (*fin == ' ' || *fin == '\t' || *fin == '\n' || *fin == '\r'))
        fin--;
    int newLen = fin - s + 1;
    char *nuevo = (char *)malloc((newLen + 1) * sizeof(char));
    for (int i = 0; i < newLen; i++)
        nuevo[i] = s[i];
    nuevo[newLen] = '\0';
    return nuevo;
}