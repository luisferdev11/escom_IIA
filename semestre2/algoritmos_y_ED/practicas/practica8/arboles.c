#include "arboles.h"

#include "expresiones.h"

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

void eliminarNodoArbol(Arbol* raiz, Dato valorEliminar) {
    if (*raiz == NULL) return;

    // Comparar la prioridad (valor) para decidir en qué dirección proceder
    if (valorEliminar.valor < (*raiz)->info.valor) {
        eliminarNodoArbol(&((*raiz)->izq), valorEliminar);
    } else if (valorEliminar.valor > (*raiz)->info.valor) {
        eliminarNodoArbol(&((*raiz)->der), valorEliminar);
    } else {
        // Caso en que se encontró el nodo a eliminar
        if ((*raiz)->izq == NULL && (*raiz)->der == NULL) {
            // Nodo sin hijos
            free(*raiz);
            *raiz = NULL;
        } else if ((*raiz)->izq == NULL) {
            // Nodo con solo hijo derecho
            Arbol temp = *raiz;
            *raiz = (*raiz)->der;
            free(temp);
        } else if ((*raiz)->der == NULL) {
            // Nodo con solo hijo izquierdo
            Arbol temp = *raiz;
            *raiz = (*raiz)->izq;
            free(temp);
        } else {
            // Nodo con dos hijos: encontrar el sucesor inorden
            Arbol temp = nodoMinimo((*raiz)->der);
            (*raiz)->info = temp->info;
            eliminarNodoArbol(&((*raiz)->der), temp->info);
        }
    }
}

Arbol nodoMinimo(Arbol nodo) {
    while (nodo && nodo->izq != NULL) {
        nodo = nodo->izq;
    }
    return nodo;
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

void preOrden(Arbol raiz, int nivel) {
    if (raiz) {
        int hijos = 0;
        if (raiz->izq) hijos++;
        if (raiz->der) hijos++;

        // Crear una copia de la expresión
        char* expresionCopia = malloc(strlen(raiz->info.expresion) + 1);
        if (expresionCopia == NULL) {
            perror("Error al asignar memoria para la copia de la expresión");
            exit(EXIT_FAILURE);
        }
        strcpy(expresionCopia, raiz->info.expresion);

        // Evaluar la copia de la expresión
        int resultado = evaluarExpresionPosfija(expresionCopia);

        printf("Prioridad: %d, Nivel: %d, Hijos: %d, Expresión: %s, Resultado: %d\n",
               raiz->info.valor, nivel, hijos, raiz->info.expresion, resultado);

        // Liberar la memoria de la copia de la expresión
        free(expresionCopia);

        // eliminar nodo
        Arbol subArbolIzq = raiz->izq;
        Arbol subArbolDer = raiz->der;

        eliminarNodoArbol(&raiz, raiz->info);

        preOrden(subArbolIzq, nivel + 1);
        preOrden(subArbolDer, nivel + 1);
    }
}

void posOrden(Arbol raiz, int nivel) {
    if (raiz) {
        posOrden(raiz->izq, nivel + 1);
        posOrden(raiz->der, nivel + 1);

        int hijos = (raiz->izq ? 1 : 0) + (raiz->der ? 1 : 0);

        char* expresionCopia = malloc(strlen(raiz->info.expresion) + 1);
        if (expresionCopia == NULL) {
            perror("Error al asignar memoria para la copia de la expresión");
            exit(EXIT_FAILURE);
        }
        strcpy(expresionCopia, raiz->info.expresion);

        int resultado = evaluarExpresionPosfija(expresionCopia);

        printf("Prioridad: %d, Nivel: %d, Hijos: %d, Expresión: %s, Resultado: %d\n",
               raiz->info.valor, nivel, hijos, raiz->info.expresion, resultado);

        free(expresionCopia);

        eliminarNodoArbol(&raiz, raiz->info);
    }
}

void inOrden(Arbol raiz, int nivel) {
    if (raiz) {
        inOrden(raiz->izq, nivel + 1);

        int hijos = (raiz->izq ? 1 : 0) + (raiz->der ? 1 : 0);

        char* expresionCopia = malloc(strlen(raiz->info.expresion) + 1);
        if (expresionCopia == NULL) {
            perror("Error al asignar memoria para la copia de la expresión");
            exit(EXIT_FAILURE);
        }
        strcpy(expresionCopia, raiz->info.expresion);

        int resultado = evaluarExpresionPosfija(expresionCopia);

        printf("Prioridad: %d, Nivel: %d, Hijos: %d, Expresión: %s, Resultado: %d\n",
               raiz->info.valor, nivel, hijos, raiz->info.expresion, resultado);

        free(expresionCopia);

        eliminarNodoArbol(&raiz, raiz->info);

        inOrden(raiz->der, nivel + 1);
    }
}

int cantidadHojas(Arbol raiz) {
}

int alturaArbol(Arbol raiz) {
}

// Arbol nodoMinimo(Arbol raiz) {
// }