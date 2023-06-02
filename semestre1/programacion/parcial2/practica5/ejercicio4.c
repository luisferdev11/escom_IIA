#include <stdio.h>
#include <string.h>

int esPalindromo(char cadena[], int tamano) {
    for (int i = 0; i < tamano / 2; i++) {
        if (cadena[i] != cadena[tamano - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char cadena[100];  // Asumimos que la cadena no será mayor a 100 caracteres

    printf("Introduce una cadena: ");
    fgets(cadena, sizeof(cadena), stdin);  // Leer la cadena del usuario

    // Eliminamos el carácter de nueva línea que fgets añade al final de la cadena
    cadena[strcspn(cadena, "\n")] = 0;

    int tamano = strlen(cadena);  // Obtenemos el tamaño de la cadena

    if (esPalindromo(cadena, tamano) == 1) {
        printf("La cadena es un palíndromo.\n");
    } else {
        printf("La cadena no es un palíndromo.\n");
    }

    return 0;
}
