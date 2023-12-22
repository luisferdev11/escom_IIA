/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
8-nov-2023
*/

#include "PilaDinamica.h"

#include <ctype.h>

void crearPila(Pila* p) {
    p->cima = NULL;
    p->cursor = -1;
    puts("Pila creada satisfactoriamente");
}

/*  Pila* crearPila2(){
    Pila *p=(Pila *)malloc(sizeof(Pila));
    p->cima=NULL;
    p->cursor=-1;
}  */

bool apilar(Pila* p, Data dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo != NULL) {
        nuevoNodo->info = dato;
        nuevoNodo->siguiente = p->cima;
        p->cima = nuevoNodo;
        p->cursor++;
        return true;
    } else {
        puts("La pila esta llena");
        return false;
    }
}

Data desapilar(Pila* p) {
    if (estaVacia(*p)) {
        puts("No hay elementos en la pila");
        Data aux;
        return aux;
    } else {
        Data informacion = p->cima->info;
        struct Nodo* aux = p->cima;
        p->cima = p->cima->siguiente;
        p->cursor--;
        free(aux);
        return informacion;
    }
}

void consultarCima(Pila p) {
    printf("El valor en la cima es:%d\n", p.cima->info.valor);
}

void destruirPila(Pila* p) {
    vaciarPila(p);
    // free(p);
}

void vaciarPila(Pila* p) {
    while (!estaVacia(*p)) {
        Data info = desapilar(p);
        printf("Dato extraido:%d\n", info.valor);
    }
}

bool estaVacia(Pila p) {
    if (p.cima == NULL) { /*p.cursor=-1*/
        return true;
    } else {
        return false;
    }
}

int evaluarPosfija(char* expresion) {
    Pila p;
    crearPila(&p);
    int i = 0;
    int valor, a, b;
    Data dato;

    while (expresion[i] != '\0') {
        if (isdigit(expresion[i])) {
            dato.valor = expresion[i] - '0';
            apilar(&p, dato);
        } else {
            b = desapilar(&p).valor;
            a = desapilar(&p).valor;

            switch (expresion[i]) {
                case '+':
                    valor = a + b;
                    break;
                case '-':
                    valor = a - b;
                    break;
                case '*':
                    valor = a * b;
                    break;
                case '/':
                    valor = a / b;
                    break;
                default:
                    printf("Operador no soportado: %c\n", expresion[i]);
                    return -1;
            }
            dato.valor = valor;
            apilar(&p, dato);
        }
        i++;
    }

    valor = desapilar(&p).valor;
    destruirPila(&p);
    return valor;
}

void main() {
    char* nombreArchivo = "expresion.txt";
    FILE* archivo = fopen(nombreArchivo, "r");  // Abrir el archivo en modo de lectura
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Asumiendo que la expresión no será más larga que 255 caracteres
    char expresionPosfija[256];

    // Leer la línea (expresión posfija) del archivo
    if (fgets(expresionPosfija, sizeof(expresionPosfija), archivo) == NULL) {
        perror("Error al leer la expresión del archivo");
        fclose(archivo);  // No olvidar cerrar el archivo
        exit(EXIT_FAILURE);
    }

    // Cerrar el archivo ya que hemos terminado de leer la expresión
    fclose(archivo);

    // Ahora expresionPosfija contiene la expresión leída del archivo
    int resultado = evaluarPosfija(expresionPosfija);
    printf("El resultado de la expresión posfija '%s' es: %d\n", expresionPosfija, resultado);
}