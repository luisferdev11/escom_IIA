#include <stdio.h>

#define MAX_SIZE 1000  // Tamaño máximo del arreglo de texto

// void lee(char *vec) {
//     if ((vec = getchar()) == EOF) /* EOF se teclea: CTRL-Z */
//         ;
//     else
//         lee(vec + 1);
// }

// Función para leer el texto del teclado de manera recursiva
void lee(char *vec) {
    int ch = getchar();
    if (ch == EOF) {
        *vec = '\0';  // Terminar la cadena correctamente
    } else {
        *vec = (char)ch;
        lee(vec + 1);  // Llama recursivamente para el siguiente caracter
    }
}

// Función recursiva para contar caracteres, palabras y renglones
void cuenta(char *vec, int *caracteres, int *palabras, int *renglones, char prevChar) {
    if (*vec == '\0') {  // Caso base: fin del arreglo
        // Añadir la última palabra y renglón si es necesario
        if (prevChar != ' ' && prevChar != '\n' && prevChar != '\t') {
            (*palabras)++;
        }
        if (prevChar != '\n') {
            (*renglones)++;
        }
        return;
    }

    // Incrementar contador de caracteres
    (*caracteres)++;

    // Contar renglones
    if (*vec == '\n') {
        (*renglones)++;
    }

    // Contar palabras
    if ((*vec == ' ' || *vec == '\n' || *vec == '\t') && (prevChar != ' ' && prevChar != '\n' && prevChar != '\t')) {
        (*palabras)++;
    }

    // Recursión con el siguiente caracter
    cuenta(vec + 1, caracteres, palabras, renglones, *vec);
}

int main() {
    char texto[MAX_SIZE];  // Arreglo para almacenar el texto
    int caracteres = 0, palabras = 0, renglones = 0;

    printf("Introduce el texto (CTRL+Z para terminar en Windows, CTRL+D en UNIX):\n");
    lee(texto);  // Llamada a la función que lee el texto usando notación de apuntadores

    cuenta(texto, &caracteres, &palabras, &renglones, ' ');  // Iniciar con un espacio como carácter previo

    printf("Renglones: %d, Palabras: %d, Caracteres: %d\n", renglones, palabras, caracteres);

    return 0;
}
