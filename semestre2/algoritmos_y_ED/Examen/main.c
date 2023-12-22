
// #include "arboles.h"

// int main() {
//     Arbol miArbol = NULL;
//     Dato valor;

//     // Insertar nodos en el árbol
//     valor.valor = 10;
//     insertarNodoArbol(&miArbol, valor);
//     valor.valor = 5;
//     insertarNodoArbol(&miArbol, valor);
//     valor.valor = 15;
//     insertarNodoArbol(&miArbol, valor);
//     valor.valor = 3;
//     insertarNodoArbol(&miArbol, valor);
//     valor.valor = 7;
//     insertarNodoArbol(&miArbol, valor);

//     // Mostrar el árbol en diferentes órdenes
//     printf("Preorden: ");
//     preOrden(miArbol);
//     printf("\nInorden: ");
//     inOrden(miArbol);
//     printf("\nPosorden: ");
//     posOrden(miArbol);

//     // Calcular y mostrar la altura del árbol
//     printf("\nAltura del árbol: %d\n", alturaArbol(miArbol));

//     // Calcular y mostrar la cantidad de hojas
//     printf("Cantidad de hojas: %d\n", cantidadHojas(miArbol));

//     // Encontrar y mostrar el nodo mínimo
//     Arbol minimo = nodoMinimo(miArbol);
//     if (minimo) {
//         printf("Nodo mínimo: %d\n", minimo->info.valor);
//     }

//     // Eliminar un nodo y mostrar el árbol de nuevo
//     valor.valor = 5;
//     eliminarNodoArbol(&miArbol, valor);
//     printf("Árbol después de eliminar el nodo con valor 5:\nInorden: ");
//     inOrden(miArbol);
//     printf("\n");

//     // Liberar la memoria del árbol
//     eliminarArbol(&miArbol);

//     return 0;
// }

// #include "lista_circular.h"

// int main() {
//     ListaCircular* miLista = crearLista();
//     Dato valor;

//     // Insertar elementos en la lista
//     valor.valor = 40;
//     insertarFinal(miLista, valor);
//     valor.valor = 20;
//     insertarFinal(miLista, valor);
//     valor.valor = 30;
//     insertarFinal(miLista, valor);

//     // Mostrar la lista
//     printf("Lista después de inserciones: ");
//     mostrarLista(miLista);

//     // Insertar al inicio
//     valor.valor = 50;
//     insertarInicio(miLista, valor);
//     printf("Lista después de insertar al inicio: ");
//     mostrarLista(miLista);

//     // Ordenar la lista
//     ordenaSeleccion(miLista);
//     printf("Lista después de ordenar: ");
//     mostrarLista(miLista);

//     // Eliminar el último elemento
//     eliminarFinal(miLista);
//     printf("Lista después de eliminar el último elemento: ");
//     mostrarLista(miLista);

//     // Buscar un elemento en la lista
//     valor.valor = 20;
//     Nodo* encontrado = buscar(miLista, valor);
//     if (encontrado) {
//         printf("Elemento encontrado: %d\n", encontrado->dato.valor);
//     } else {
//         printf("Elemento no encontrado\n");
//     }

//     // Eliminar el primer elemento
//     eliminarInicio(miLista);
//     printf("Lista después de eliminar el primer elemento: ");
//     mostrarLista(miLista);

//     // Liberar la memoria de la lista
//     liberarLista(miLista);

//     return 0;
// }

#include "cola.h"

// int main() {
//     Cola* miCola = crearCola();
//     Dato valor, valorExtraido;

//     // Encolar elementos
//     valor.valor = 10;
//     encolar(miCola, valor);
//     valor.valor = 20;
//     encolar(miCola, valor);
//     valor.valor = 30;
//     encolar(miCola, valor);

//     // Mostrar la cola
//     printf("Cola después de inserciones: ");
//     mostrarCola(miCola);

//     // Desencolar un elemento y mostrarlo
//     if (desencolar(miCola, &valorExtraido)) {
//         printf("Elemento desencolado: %d\n", valorExtraido.valor);
//     }
//     mostrarCola(miCola);

//     // Observar el elemento frontal sin desencolarlo
//     if (frenteCola(miCola, &valorExtraido)) {
//         printf("Elemento en frente de la cola: %d\n", valorExtraido.valor);
//     }

//     // Desencolar otro elemento
//     if (desencolar(miCola, &valorExtraido)) {
//         printf("Elemento desencolado: %d\n", valorExtraido.valor);
//     }

//     // Comprobar si la cola está vacía
//     if (esColaVacia(miCola)) {
//         printf("La cola está vacía\n");
//     } else {
//         printf("La cola no está vacía\n");
//     }

//     mostrarCola(miCola);

//     // Liberar la memoria de la cola
//     liberarCola(miCola);

//     mostrarCola(miCola);
//     return 0;
// }

#include <string.h>

#include "lista_circular.h"
#define MAX_CHAR 256
#define MAX_CODIGO_LONGITUD 100

typedef struct {
    char caracter;
    char* codigo;
} CodigoHuffman;

void generarCodigosDFS(Arbol raiz, char* codigo, int longitud, CodigoHuffman* codigos, int* indice) {
    if (raiz) {
        // Si es un nodo hoja, almacena el carácter y su código
        if (!raiz->izq && !raiz->der) {
            codigos[*indice].caracter = raiz->info.caracter;
            codigos[*indice].codigo = (char*)malloc(longitud + 1);
            strncpy(codigos[*indice].codigo, codigo, longitud);
            codigos[*indice].codigo[longitud] = '\0';
            (*indice)++;
            return;
        }

        // Añadir un '0' si vamos a la izquierda, '1' si vamos a la derecha
        codigo[longitud] = '0';
        generarCodigosDFS(raiz->izq, codigo, longitud + 1, codigos, indice);

        codigo[longitud] = '1';

        generarCodigosDFS(raiz->der, codigo, longitud + 1, codigos, indice);
    }
}

void generarCodigosHuffman(Arbol arbolHuffman, CodigoHuffman* codigos, int* numCodigos) {
    char codigo[MAX_CODIGO_LONGITUD];
    generarCodigosDFS(arbolHuffman, codigo, 0, codigos, numCodigos);
}

void codificarTexto(const char* nombreArchivoEntrada, const char* nombreArchivoSalida, CodigoHuffman* codigos, int numCodigos) {
    FILE* archivoEntrada = fopen(nombreArchivoEntrada, "r");
    FILE* archivoSalida = fopen(nombreArchivoSalida, "w");
    char ch;

    if (archivoEntrada == NULL || archivoSalida == NULL) {
        perror("Error al abrir los archivos");
        return;
    }

    while ((ch = fgetc(archivoEntrada)) != EOF) {
        // Buscar el código de Huffman para el carácter actual
        for (int i = 0; i < numCodigos; i++) {
            if (codigos[i].caracter == ch) {
                fputs(codigos[i].codigo, archivoSalida);
                break;
            }
        }
    }

    fclose(archivoEntrada);
    fclose(archivoSalida);
}

// Función para calcular las frecuencias y devolver una lista circular
ListaCircular* calcularFrecuencias(const char* nombreArchivo) {
    ListaCircular* listaFrecuencias = crearLista();
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return listaFrecuencias;
    }

    int caracter;
    Dato_lcde datos[MAX_CHAR];
    for (int i = 0; i < MAX_CHAR; i++) {
        datos[i].arbol = crearNodoArbol((Dato_arbol){.valor = 0, .caracter = '\0', .frecuencia = 0});
    }

    while ((caracter = fgetc(archivo)) != EOF) {
        if (datos[caracter].arbol == NULL) {
            datos[caracter].arbol = crearNodoArbol((Dato_arbol){.valor = 0, .caracter = '\0', .frecuencia = 0});
        }
        datos[caracter].arbol->info.caracter = (char)caracter;
        datos[caracter].arbol->info.frecuencia++;
    }

    for (int i = 0; i < MAX_CHAR; i++) {
        if (datos[i].arbol->info.frecuencia > 0) {
            insertarFinal(listaFrecuencias, datos[i]);
        }
    }

    fclose(archivo);

    return listaFrecuencias;
}

// Función para combinar dos nodos de la lista en un nuevo nodo de árbol
Nodo_lcde* combinarNodos(Nodo_lcde* nodo1, Nodo_lcde* nodo2) {
    // Crear un nuevo nodo del árbol con la suma de las frecuencias
    Dato_arbol nuevoDato = {0, '\0', nodo1->dato.arbol->info.frecuencia + nodo2->dato.arbol->info.frecuencia};
    Arbol nuevoArbol = crearNodoArbol(nuevoDato);  // Asumiendo que esta función está definida en arboles.c

    // Configurar los hijos izquierdo y derecho del nuevo árbol
    nuevoArbol->izq = nodo1->dato.arbol;
    nuevoArbol->der = nodo2->dato.arbol;

    Dato_lcde nuevoDatoLCDE = {0, nuevoArbol};
    // Crear un nuevo nodo para la lista circular y asignar el nuevo árbol
    Nodo_lcde* nuevoNodo = crearNodoLCDE(nuevoDatoLCDE);  // Asumiendo que esta función está definida en lista_circular.c
    return nuevoNodo;
}

// Función para crear el Árbol de Huffman a partir de la lista circular
Arbol crearArbolHuffman(ListaCircular* lista) {
    int tamaño = longitud(lista);

    while (tamaño > 1) {  // Asumiendo que ListaCircular tiene un campo tamaño
        // Extraer los dos nodos con menor frecuencia
        Nodo_lcde* nodo1 = extraerMenor(lista);  // Asumiendo que esta función está definida
        Nodo_lcde* nodo2 = extraerMenor(lista);  // Asumiendo que esta función está definida

        // Combinar los nodos y obtener un nuevo nodo
        Nodo_lcde* nuevoNodo = combinarNodos(nodo1, nodo2);

        // Insertar el nuevo nodo en la lista, manteniendo el orden por frecuencia
        // insertarOrdenado(lista, nuevoNodo);  // Asumiendo que esta función está definida

        insertarFinal(lista, nuevoNodo->dato);

        tamaño = longitud(lista);
        printf("Tamaño de la lista temporal: %d\n", tamaño);
    }

    printf("Tamaño de la lista terminando while: %d\n", tamaño);

    // Al final, el último nodo en la lista es la raíz del Árbol de Huffman
    return lista->cabeza->dato.arbol;  // Asumiendo que ListaCircular tiene una cabeza
}

void decodificarTexto(const char* nombreArchivoCodificado, const char* nombreArchivoDecodificado, Arbol arbolHuffman) {
    FILE* archivoCodificado = fopen(nombreArchivoCodificado, "r");
    FILE* archivoDecodificado = fopen(nombreArchivoDecodificado, "w");
    char bit;
    Arbol actual = arbolHuffman;

    if (archivoCodificado == NULL || archivoDecodificado == NULL) {
        perror("Error al abrir los archivos");
        return;
    }

    while ((bit = fgetc(archivoCodificado)) != EOF) {
        if (bit == '0') {
            actual = actual->izq;
        } else if (bit == '1') {
            actual = actual->der;
        }

        // Si es un nodo hoja, escribe el carácter y reinicia al nodo raíz
        if (!actual->izq && !actual->der) {
            fputc(actual->info.caracter, archivoDecodificado);
            actual = arbolHuffman;
        }
    }

    fclose(archivoCodificado);
    fclose(archivoDecodificado);
}

int main() {
    // Definir el nombre del archivo
    const char* nombreArchivo = "ey.txt";

    // Calcular frecuencias y obtener la lista circular
    ListaCircular* listaFrecuencias = calcularFrecuencias(nombreArchivo);

    // Mostrar las frecuencias
    mostrarLista(listaFrecuencias);

    ordenaSeleccion(listaFrecuencias);
    mostrarLista(listaFrecuencias);

    Arbol arbolHuffman = crearArbolHuffman(listaFrecuencias);

    // Mostrar el árbol de Huffman
    printf("Árbol de Huffman:\n");
    inOrden(arbolHuffman);

    CodigoHuffman codigos[MAX_CHAR];  // Asegúrate de definir un tamaño adecuado
    int numCodigos = 0;
    generarCodigosHuffman(arbolHuffman, codigos, &numCodigos);

    printf("\nCodigos de Huffman:\n");
    for (int i = 0; i < numCodigos; i++) {
        printf("Caracter: %c, Código: %s\n", codigos[i].caracter, codigos[i].codigo);
    }

    // Codificar el texto y guardarlo en un archivo
    codificarTexto(nombreArchivo, "archivo_codificado.txt", codigos, numCodigos);

    decodificarTexto("archivo_codificado.txt", "archivo_decodificado.txt", arbolHuffman);

    // Liberar la memoria de la lista
    liberarLista(listaFrecuencias);

    return 0;
}