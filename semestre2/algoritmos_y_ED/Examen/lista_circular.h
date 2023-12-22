#include <stdio.h>
#include <stdlib.h>

#include "arboles.h"

// Estructura para el dato almacenado
typedef struct {
    int valor;  // Para valores enteros
    Arbol arbol;
} Dato_lcde;

// Estructura de un nodo de la lista circular doblemente enlazada
typedef struct Nodo_lcde {
    Dato_lcde dato;
    struct Nodo_lcde* siguiente;
    struct Nodo_lcde* anterior;
} Nodo_lcde;

// Estructura de la lista circular
typedef struct {
    Nodo_lcde* cabeza;
} ListaCircular;

// Prototipos de funciones
ListaCircular* crearLista();
Nodo_lcde* crearNodoLCDE(Dato_lcde dato);
void insertarInicio(ListaCircular* lista, Dato_lcde dato);
void insertarFinal(ListaCircular* lista, Dato_lcde dato);
void eliminarInicio(ListaCircular* lista);
void eliminarFinal(ListaCircular* lista);
Nodo_lcde* buscar(ListaCircular* lista, Dato_lcde dato);
void mostrarLista(ListaCircular* lista);
void liberarLista(ListaCircular* lista);
void ordenaSeleccion(ListaCircular* lista);
int longitud(ListaCircular* lista);
Nodo_lcde* extraerMenor(ListaCircular* lista);
Nodo_lcde* combinarNodos(Nodo_lcde* nodo1, Nodo_lcde* nodo2);
