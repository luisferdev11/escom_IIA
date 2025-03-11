#ifndef CADENAS_H
#define CADENAS_H

#include <stdio.h>
#include <stdlib.h>

#define LAMBDA "λ"

// Funciones para manipulación de cadenas
int longitud_cadena(const char *s);
char* obtener_prefijo(const char *s, int n);
char* obtener_sufijo(const char *s, int n);
void imprimir_prefijo_sufijo(const char *s, int n);
char* obtener_subcadena(const char *s, int n, int m);
char* remover_subsecuencia(const char *s, int posiciones[], int count);
char* invertir_cadena(const char *s);
char* concatenar(const char *s1, const char *s2);
char* potencia(const char *s, int pot);
char* potencia_inversa(const char *s, int pot);
char* copia_cadena(const char *s); // Función para duplicar una cadena

#endif // CADENAS_H
