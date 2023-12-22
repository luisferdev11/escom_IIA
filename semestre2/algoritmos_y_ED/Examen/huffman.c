#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* Estructura de un nodo del árbol */
typedef struct nodo arbol;
struct nodo {
    int frecuencia;
    char dato;
    arbol *derecho;
    arbol *izquierdo;
};
/* Mensaje de ERROR */
void error(void) {
    perror("\n\t\aERROR: Memoria insuficiente...");
    exit(1);
}
/* Crea un nuevo nodo del tipo de la estructura */
arbol *Nuevo() {
    arbol *q = (arbol *)malloc(sizeof(arbol));
    if (!q) error();
    return (q);
}

/* Inserta un nuevo nodo en el árbol */
arbol *insertar(char dato, int x) {
    arbol *q;
    q = Nuevo();
    q->frecuencia = x;
    q->dato = dato;
    q->derecho = q->izquierdo = NULL;
    return (q);
}
/* Ordena los nodos del árbol de acuerdo a su frecuencia */
void ordenar(arbol *a[], int n) { /* Ripple Sort */
    int i, j;
    arbol *temp;
    for (i = 0; i < n - 1; i++)
        for (j = i; j < n; j++)
            if (a[i]->frecuencia > a[j]->frecuencia) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
}
/* Asigna un código a cada carácter */
void asigna_codigo(arbol *p, int c[], int n) {
    int i;
    if ((p->izquierdo == NULL) && (p->derecho == NULL)) {
        printf("\n\t%c Código : ", p->dato);
        for (i = 0; i < n; i++) printf("%d", c[i]);
    } else {
        c[n] = 0;
        n++;
        asigna_codigo(p->izquierdo, c, n);
        c[n - 1] = 1;
        asigna_codigo(p->derecho, c, n);
    }
}
/* Borra el árbol creado */
void borra_arbol(arbol *p) {
    if (p != NULL) {
        borra_arbol(p->izquierdo);
        borra_arbol(p->derecho);
        free(p);
    }
}
/* Programa Principal */
void main(void) {
    arbol *p1;
    int i, j, n, u, c[20];
    char dato;
    arbol *a[10]; /* Hasta 10 subárboles de inicio */
    int frecuencia;
    printf("Código de Huffman");
    printf("\n\n\tEntra el número de caracteres a codificar: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("\n\tEntra Carácter y Frecuencia: ");
        scanf(" %c", &dato);  // Cambiado para manejar correctamente la entrada del carácter.
        scanf("%d", &frecuencia);
        a[i] = insertar(dato, frecuencia);
    }
    while (n > 1) {
        ordenar(a, n);
        u = a[0]->frecuencia + a[1]->frecuencia;
        dato = a[1]->dato;
        p1 = insertar(dato, u);
        p1->derecho = a[1];
        p1->izquierdo = a[0];
        a[0] = p1;
        for (j = 1; j < n - 1; j++) a[j] = a[j + 1];
        n--;
    }
    asigna_codigo(a[0], c, 0);
    getchar();
    borra_arbol(a[0]);
}
