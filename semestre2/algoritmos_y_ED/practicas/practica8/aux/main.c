#include "arboles.h"

int main() {
    Arbol miArbol = NULL;
    Dato valor;

    // Insertar nodos
    valor.valor = 50;
    insertarNodoArbol(&miArbol, valor);
    valor.valor = 30;
    insertarNodoArbol(&miArbol, valor);
    valor.valor = 70;
    insertarNodoArbol(&miArbol, valor);
    valor.valor = 20;
    insertarNodoArbol(&miArbol, valor);
    valor.valor = 40;
    insertarNodoArbol(&miArbol, valor);
    valor.valor = 60;
    insertarNodoArbol(&miArbol, valor);
    valor.valor = 80;
    insertarNodoArbol(&miArbol, valor);

    // Recorrer el árbol antes de la eliminación
    printf("Posorden antes de la eliminación: ");
    posOrden(miArbol);
    printf("\n");

    // Eliminar un nodo
    valor.valor = 70;
    eliminarNodoArbol(&miArbol, valor);

    // Recorrer el árbol después de la eliminación
    printf("Posorden después de la eliminación: ");
    posOrden(miArbol);
    printf("\n");

    // Eliminar el árbol
    eliminarArbol(&miArbol);

    return 0;
}
