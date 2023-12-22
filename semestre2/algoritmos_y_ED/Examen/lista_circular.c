
#include "lista_circular.h"

// Función para crear una nueva lista circular
ListaCircular* crearLista() {
    ListaCircular* nuevaLista = (ListaCircular*)malloc(sizeof(ListaCircular));
    if (!nuevaLista) {
        perror("Error al crear la lista");
        return NULL;
    }
    nuevaLista->cabeza = NULL;
    return nuevaLista;
}

// Función para crear un nuevo nodo
Nodo_lcde* crearNodoLCDE(Dato_lcde dato) {
    Nodo_lcde* nuevoNodo = (Nodo_lcde*)malloc(sizeof(Nodo_lcde));
    if (!nuevoNodo) {
        perror("Error al crear el nodo");
        return NULL;
    }
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = nuevoNodo->anterior = NULL;
    return nuevoNodo;
}

// Función para insertar un nodo al inicio de la lista
void insertarInicio(ListaCircular* lista, Dato_lcde dato) {
    Nodo_lcde* nuevoNodo = crearNodoLCDE(dato);
    if (!lista->cabeza) {
        lista->cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo->anterior = nuevoNodo;
    } else {
        Nodo_lcde* ultimo = lista->cabeza->anterior;
        nuevoNodo->siguiente = lista->cabeza;
        nuevoNodo->anterior = ultimo;
        lista->cabeza->anterior = nuevoNodo;
        ultimo->siguiente = nuevoNodo;
        lista->cabeza = nuevoNodo;
    }
}

// Función para insertar un nodo al final de la lista
void insertarFinal(ListaCircular* lista, Dato_lcde dato) {
    Nodo_lcde* nuevoNodo = crearNodoLCDE(dato);
    if (!lista->cabeza) {
        lista->cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo->anterior = nuevoNodo;
    } else {
        Nodo_lcde* ultimo = lista->cabeza->anterior;
        nuevoNodo->siguiente = lista->cabeza;
        nuevoNodo->anterior = ultimo;
        ultimo->siguiente = nuevoNodo;
        lista->cabeza->anterior = nuevoNodo;
    }
}

// Función para eliminar el nodo del inicio de la lista
void eliminarInicio(ListaCircular* lista) {
    if (lista->cabeza) {
        Nodo_lcde* temp = lista->cabeza;
        if (lista->cabeza->siguiente == lista->cabeza) {  // Solo un elemento en la lista
            lista->cabeza = NULL;
        } else {
            Nodo_lcde* ultimo = lista->cabeza->anterior;
            lista->cabeza = lista->cabeza->siguiente;
            lista->cabeza->anterior = ultimo;
            ultimo->siguiente = lista->cabeza;
        }
        free(temp);
    }
}

// Función para eliminar el nodo del final de la lista
void eliminarFinal(ListaCircular* lista) {
    if (lista->cabeza) {
        Nodo_lcde* ultimo = lista->cabeza->anterior;
        if (lista->cabeza->siguiente == lista->cabeza) {  // Solo un elemento en la lista
            lista->cabeza = NULL;
        } else {
            Nodo_lcde* penultimo = ultimo->anterior;
            penultimo->siguiente = lista->cabeza;
            lista->cabeza->anterior = penultimo;
        }
        free(ultimo);
    }
}

// Función para buscar un nodo en la lista
Nodo_lcde* buscar(ListaCircular* lista, Dato_lcde dato) {
    Nodo_lcde* actual = lista->cabeza;
    if (actual) {
        do {
            if (actual->dato.valor == dato.valor) {
                return actual;
            }
            actual = actual->siguiente;
        } while (actual != lista->cabeza);
    }
    return NULL;
}

// Función para mostrar todos los elementos de la lista
void mostrarLista(ListaCircular* lista) {
    Nodo_lcde* actual = lista->cabeza;
    if (actual) {
        do {
            printf("Caracter: '%c', Frecuencia: %d\n", actual->dato.arbol->info.caracter, actual->dato.arbol->info.frecuencia);
            actual = actual->siguiente;
        } while (actual != lista->cabeza);
        printf("\n");
    }
}

// Función para liberar la memoria de la lista
void liberarLista(ListaCircular* lista) {
    if (lista->cabeza) {
        Nodo_lcde* actual = lista->cabeza;
        do {
            Nodo_lcde* temp = actual;
            actual = actual->siguiente;
            free(temp);
        } while (actual != lista->cabeza);
    }
    free(lista);
}

// void ordenaSeleccion(ListaCircular* lista) {
//     if (!lista || !lista->cabeza) return;

//     Nodo_lcde *actual, *siguiente, *minimo;
//     Dato_lcde temp;

//     for (actual = lista->cabeza; actual->siguiente != lista->cabeza; actual = actual->siguiente) {
//         minimo = actual;
//         for (siguiente = actual->siguiente; siguiente != lista->cabeza; siguiente = siguiente->siguiente) {
//             if (siguiente->dato.valor < minimo->dato.valor) {
//                 minimo = siguiente;
//             }
//         }
//         if (minimo != actual) {
//             temp = actual->dato;
//             actual->dato = minimo->dato;
//             minimo->dato = temp;
//         }
//     }
// }

void ordenaSeleccion(ListaCircular* lista) {
    if (lista == NULL || lista->cabeza == NULL) return;

    Nodo_lcde* ultimo = lista->cabeza->anterior;  // Referencia al último nodo
    Nodo_lcde* actual = lista->cabeza;

    while (actual != ultimo) {
        Nodo_lcde* minimo = actual;
        Nodo_lcde* it = actual->siguiente;

        // Buscar el mínimo en el resto de la lista
        do {
            if (it->dato.arbol->info.frecuencia < minimo->dato.arbol->info.frecuencia) {
                minimo = it;
            }
            it = it->siguiente;
        } while (it != lista->cabeza);

        // Intercambiar datos si es necesario
        if (actual != minimo) {
            Dato_lcde temp = actual->dato;
            actual->dato = minimo->dato;
            minimo->dato = temp;
        }

        // Avanzar al siguiente nodo, pero detenerse en el penúltimo
        if (actual->siguiente == ultimo) {
            break;
        }
        actual = actual->siguiente;
    }
}

int longitud(ListaCircular* lista) {
    int contador = 0;
    Nodo_lcde* actual = lista->cabeza;
    if (actual) {
        do {
            contador++;
            actual = actual->siguiente;
        } while (actual != lista->cabeza);
    }
    return contador;
}

Nodo_lcde* extraerMenor(ListaCircular* lista) {
    if (lista == NULL || lista->cabeza == NULL) {
        return NULL;  // La lista está vacía o no está inicializada
    }

    Nodo_lcde* menor = lista->cabeza;

    // Si solo hay un nodo en la lista
    if (menor->siguiente == menor) {
        lista->cabeza = NULL;  // La lista quedará vacía
    } else {
        // Ajustar los enlaces para remover el nodo cabeza
        menor->siguiente->anterior = menor->anterior;
        menor->anterior->siguiente = menor->siguiente;
        lista->cabeza = menor->siguiente;  // Nueva cabeza de la lista
    }

    menor->siguiente = menor->anterior = NULL;  // Desvincular el nodo extraído de la lista
    return menor;
}

// void insertarOrdenado(ListaCircular* lista, Nodo_lcde* nuevoNodo) {
//     if (lista == NULL || nuevoNodo == NULL) {
//         return;  // Lista no inicializada o nuevoNodo es NULL
//     }

//     if (lista->cabeza == NULL) {
//         // La lista está vacía, insertar como único elemento
//         lista->cabeza = nuevoNodo;
//         nuevoNodo->siguiente = nuevoNodo->anterior = nuevoNodo;
//         return;
//     }

//     Nodo_lcde* actual = lista->cabeza;
//     do {
//         if (nuevoNodo->dato.arbol->info.frecuencia <= actual->dato.arbol->info.frecuencia) {
//             // Insertar antes del nodo actual
//             nuevoNodo->siguiente = actual;
//             nuevoNodo->anterior = actual->anterior;
//             actual->anterior->siguiente = nuevoNodo;
//             actual->anterior = nuevoNodo;
//             if (actual == lista->cabeza) {
//                 lista->cabeza = nuevoNodo;  // Actualizar la cabeza si se inserta al inicio
//             }
//             return;
//         }
//         actual = actual->siguiente;
//     } while (actual != lista->cabeza);

//     // Insertar al final de la lista
//     actual->anterior->siguiente = nuevoNodo;
//     nuevoNodo->anterior = actual->anterior;
//     nuevoNodo->siguiente = actual;
//     actual->anterior = nuevoNodo;
// }
