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
    if (*raiz == NULL) {
        return;  // Nodo no encontrado.
    }

    if (valorEliminar.valor < (*raiz)->info.valor) {
        eliminarNodoArbol(&((*raiz)->izq), valorEliminar);
    } else if (valorEliminar.valor > (*raiz)->info.valor) {
        eliminarNodoArbol(&((*raiz)->der), valorEliminar);
    } else {
        // Nodo encontrado
        Arbol aux = *raiz;
        if ((*raiz)->izq == NULL) {
            *raiz = (*raiz)->der;
        } else if ((*raiz)->der == NULL) {
            *raiz = (*raiz)->izq;
        } else {
            aux = nodoMinimo((*raiz)->der);
            (*raiz)->info = aux->info;
            eliminarNodoArbol(&((*raiz)->der), aux->info);
            return;  // Evita doble liberación
        }
        free(aux);
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
    while (raiz && raiz->izq != NULL) {
        raiz = raiz->izq;
    }
    return raiz;
}