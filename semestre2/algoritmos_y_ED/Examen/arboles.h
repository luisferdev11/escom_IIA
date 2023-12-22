#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;
    char caracter;
    int frecuencia;
} Dato_arbol;

// TDA Arbol BST
typedef struct Nodo_arbolito {
    Dato_arbol info;
    struct Nodo_arbolito* der;
    struct Nodo_arbolito* izq;
} Nodo_de_Arbol_BST;

typedef Nodo_de_Arbol_BST* Arbol;

Arbol crearNodoArbol(Dato_arbol valorUsuario);
void nuevoArbol(Arbol* raiz, Dato_arbol valorUsuario, Arbol hIzq, Arbol hDer);
void eliminarArbol(Arbol* raiz);
void eliminarNodoArbol(Arbol* raiz, Dato_arbol valorEliminar);
void insertarNodoArbol(Arbol* raiz, Dato_arbol valorUsuario);
void buscarNodo(Arbol* raiz, Dato_arbol elementoBuscado, Arbol* nodoEncontrado);
void preOrden(Arbol raiz);
void posOrden(Arbol raiz);
void inOrden(Arbol raiz);
void reemplazar(Arbol* raiz);
int cantidadHojas(Arbol raiz);
int alturaArbol(Arbol raiz);
Arbol nodoMinimo(Arbol raiz);
