#include "huffman.h"
#define MAX_CODIGO_LONGITUD 100

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

void decodificarTextoConCola(const char* nombreArchivoCodificado, const char* nombreArchivoDecodificado, Arbol arbolHuffman) {
    FILE* archivoCodificado = fopen(nombreArchivoCodificado, "r");
    FILE* archivoDecodificado = fopen(nombreArchivoDecodificado, "w");
    Cola* cola = crearCola();
    char bit;
    Arbol actual = arbolHuffman;
    Dato_cola dato;

    if (archivoCodificado == NULL || archivoDecodificado == NULL) {
        perror("Error al abrir los archivos");
        return;
    }

    // Encolar cada bit del archivo codificado en la cola
    while ((bit = fgetc(archivoCodificado)) != EOF) {
        if (bit == '0' || bit == '1') {
            dato.valor = bit - '0';  // Convierte el caracter '0' o '1' a entero 0 o 1
            encolar(cola, dato);
        }
    }

    // Procesar cada bit en la cola para decodificar
    while (!esColaVacia(cola)) {
        desencolar(cola, &dato);
        if (dato.valor == 0) {
            actual = actual->izq;
        } else {
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
    liberarCola(cola);
}