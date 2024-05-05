#include <string.h>

#include "huffman.h"

#define MAX_CHAR 256
#define MAX_CODIGO_LONGITUD 100

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

int main() {
    // Definir el nombre del archivo
    const char* nombreArchivo = "texto.txt";

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

    CodigoHuffman codigos[MAX_CHAR];
    int numCodigos = 0;
    generarCodigosHuffman(arbolHuffman, codigos, &numCodigos);

    printf("\nCodigos de Huffman:\n");
    for (int i = 0; i < numCodigos; i++) {
        printf("Caracter: %c, Código: %s\n", codigos[i].caracter, codigos[i].codigo);
    }

    // Codificar el texto y guardarlo en un archivo
    codificarTexto(nombreArchivo, "archivo_codificado.txt", codigos, numCodigos);

    decodificarTextoConCola("archivo_codificado.txt", "archivo_decodificado.txt", arbolHuffman);

    // Liberar la memoria de la lista
    liberarLista(listaFrecuencias);

    return 0;
}