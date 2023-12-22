/**
 * Nombres: Rodriguez Dominguez Luis Fernando y Montes de oca Arellano Edgar
 * Grupo: 2BV2
 * Carrera: Ingeniería en Inteligencia Artificial
 * Fecha de última modificación: 19:56 hrs 10/11/23
 */

#ifndef BICOLA_H
#define BICOLA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256  // Longitud máxima de una línea en un archivo

/**
 * Estructura para un nodo de la bicola.
 * Almacena el nombre del archivo y un puntero al siguiente nodo.
 */
typedef struct Nodo {
    char archivo[MAX_LINE_LENGTH];
    struct Nodo* siguiente;
} Nodo;

/**
 * Estructura para la bicola.
 * Contiene punteros al primer y último nodo, y un contador de nodos.
 */
typedef struct {
    Nodo* inicio;
    Nodo* fin;
    int contador;
} Bicola;

// Funciones de la bicola
void inicializarBicola(Bicola* cola);
int estaVacia(Bicola* cola);
void ingresarDerecha(Bicola* cola, char* archivo);
void ingresarIzquierda(Bicola* cola, char* archivo);
void mostrarPrimerNodo(Bicola* cola);
void mostrarTodosLosNodos(Bicola* cola);
int contarNodos(Bicola* cola);
void eliminarPrimerNodo(Bicola* cola);
void eliminarBicola(Bicola* cola);
void simularEnvioArchivo(char* archivo);

#endif  // BICOLA_H
