#include "expresiones.h"

#include "pila.h"

int evaluarExpresionPosfija(char* expresion) {
    Pila pila = NULL;
    char* token = strtok(expresion, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {
            push(&pila, atoi(token));
        } else {
            int val2 = pop(&pila);
            int val1 = pop(&pila);
            switch (token[0]) {
                case '+':
                    push(&pila, val1 + val2);
                    break;
                case '-':
                    push(&pila, val1 - val2);
                    break;
                case '*':
                    push(&pila, val1 * val2);
                    break;
                case '/':
                    push(&pila, val1 / val2);
                    break;
                default:
                    printf("Operador no reconocido");
                    exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }

    return pop(&pila);
}