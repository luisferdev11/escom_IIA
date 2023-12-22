#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char expresion[100];  // Asumiendo una longitud máxima para la expresión
    int valor;
} Dato;

// TDA Arbol BST
typedef struct Nodo {
    Dato info;
    struct Nodo* der;
    struct Nodo* izq;
} Nodo_de_Arbol_BST;

typedef Nodo_de_Arbol_BST* Arbol;

Arbol crearNodo(Dato valorUsuario);
void nuevoArbol(Arbol* raiz, Dato valorUsuario, Arbol hIzq, Arbol hDer);
void eliminarArbol(Arbol* raiz);
void eliminarNodoArbol(Arbol* raiz, Dato valorEliminar);
// void eliminarNodoArbol(Arbol* raiz, int valorEliminar);
void insertarNodoArbol(Arbol* raiz, Dato valorUsuario);
void buscarNodo(Arbol* raiz, Dato elementoBuscado, Arbol* nodoEncontrado);
void preOrden(Arbol raiz, int nivel);
void inOrden(Arbol raiz, int nivel);
void posOrden(Arbol raiz, int nivel);
void reemplazar(Arbol* raiz);
int cantidadHojas(Arbol raiz);
int alturaArbol(Arbol raiz);
Arbol nodoMinimo(Arbol raiz);
