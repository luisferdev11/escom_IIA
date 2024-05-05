#include <stdio.h>

void lee(char *);
void imprime(char *);
void bubble(char *);
int recorre(char *);
void intercambia(char *, char *);

/* int global = 0 */

void main() {
    char vec[256];
    lee(vec);  // gets(vec);
    bubble(vec);
    imprime(vec);  // puts(vec);
    /* printf("global: %d\n, global); */
}

void lee(char *vec) {
    if ((*vec = getchar()) == '\n') {
        *vec = '\0';
    } else {
        lee(vec + 1);
    }
}

void imprime(char *vec) {
    if (putchar(*vec)) {
        imprime(vec + 1);
    }
}

void bubble(char *vec) {
    if (recorre(vec))
        bubble(vec);
}

int recorre(char *vec) {
    /* global ++*/
    if ((*vec == '\0') || (*(vec + 1) == '\0'))
        return 0;
    else {
        if (*vec > *(vec + 1)) {
            intercambia(vec, vec + 1);
            return (recorre(vec + 1) + 1);
        } else {
            return (recorre(vec + 1));
        }
    }
}

void intercambia(char *alfa, char *beta) {
    char aux;
    aux = *alfa;
    *alfa = *beta;
    *beta = aux;
}

/*
TAREA
Probar con permutaciones:
    abdc
    acbd
    acdb
    ...
    24
Reporte con tablita
*/