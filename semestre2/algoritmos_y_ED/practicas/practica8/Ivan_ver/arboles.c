/*
Luis Fernando Rodriguez Dominguez
Iván Martínez Mendoza
Edgar Marin Montes de Oca
2BV2
Ingenieria en Inteligencia Artificial
8-dic-2023
*/

#include "arboles.h"

Arbol crearNodo(Dato valorUsuario) {
    Arbol raiz = (Arbol)malloc(sizeof(Nodo_de_Arbol_BST));
    if (!raiz) {
        perror("No se pudo asignar memoria para el nodo de arbol");
    } else {
        raiz->info = valorUsuario;
        raiz->der = raiz->izq = NULL;
    }
    return raiz;
}

void nuevoArbol(Arbol* raiz, Dato valorUsuario, Arbol hIzq, Arbol hDer) {
    *raiz = crearNodo(valorUsuario);
    (*raiz)->der = hDer;
    (*raiz)->izq = hIzq;
}

void eliminarArbol(Arbol* raiz) {
    if ((*raiz)) {
        eliminarArbol(&((*raiz)->izq));
        eliminarArbol(&((*raiz)->der));
        free((*raiz));
        *raiz = NULL;
    }
}

void eliminarNodoArbol(Arbol* raiz, Dato valorEliminar) {
    if ((*raiz)) {
        Arbol aux = *raiz;
        if (valorEliminar.valor == (*raiz)->info.valor) {
            puts("El nodo se encontro");
            if ((*raiz)->izq == NULL) {
                *raiz = aux->der;
            } else if ((*raiz)->der == NULL) {
                *raiz = aux->izq;
            } else {
                reemplazar(&aux);
            }
            free(aux);
            aux = NULL;
        } else if (valorEliminar.valor < (*raiz)->info.valor) {
            eliminarNodoArbol(&((*raiz)->izq), valorEliminar);
        } else {
            eliminarNodoArbol(&((*raiz)->der), valorEliminar);
        }
    }
}

void reemplazar(Arbol* raiz) {
    if ((*raiz)) {
        Arbol nodoMinimo, nodoPadre;
        nodoPadre = *raiz;
        nodoMinimo = (*raiz)->der;
        // Buscar al nodo más pequeño
        while (nodoMinimo->izq != NULL) {
            nodoPadre = nodoMinimo;
            nodoMinimo = nodoPadre->izq;
        }
        // Respaldamos el valor más pequeño
        Dato aux = nodoMinimo->info;
        (*raiz)->info.valor = 0;
        eliminarNodoArbol(raiz, nodoMinimo->info);
        (*raiz)->info = aux;
        (*raiz) = nodoMinimo;
    }
}

void insertarNodoArbol(Arbol* raiz, Dato valorUsuario) {
    if (!(*raiz)) {
        (*raiz) = crearNodo(valorUsuario);
    } else if (valorUsuario.valor >= (*raiz)->info.valor) {
        insertarNodoArbol(&((*raiz)->der), valorUsuario);
    } else if (valorUsuario.valor < (*raiz)->info.valor) {
        insertarNodoArbol(&((*raiz)->izq), valorUsuario);
    }
}

void buscarNodo(Arbol* raiz, Dato elementoBuscado, Arbol* nodoEncontrado) {
    if (raiz) {
        if (elementoBuscado.valor == (*raiz)->info.valor) {
            *nodoEncontrado = (*raiz);
        } else if (elementoBuscado.valor > (*raiz)->info.valor) {
            buscarNodo(&((*raiz)->der), elementoBuscado, nodoEncontrado);
        } else {
            buscarNodo(&((*raiz)->izq), elementoBuscado, nodoEncontrado);
        }
    }
}

void preOrden(Arbol raiz) {
    if (raiz) {
        printf("%d,", raiz->info.valor);
        preOrden(raiz->izq);
        preOrden(raiz->der);
    }
}

void posOrden(Arbol raiz) {
    if (raiz) {
        posOrden(raiz->izq);
        posOrden(raiz->der);
        printf("%d,", raiz->info.valor);
    }
}

void inOrden(Arbol raiz) {
    if (raiz) {
        inOrden(raiz->izq);
        printf("%d,", raiz->info.valor);
        inOrden(raiz->der);
    }
}

int cantidadHojas(Arbol raiz) {
}

int alturaArbol(Arbol raiz) {
}

Arbol nodoMinimo(Arbol raiz) {
}