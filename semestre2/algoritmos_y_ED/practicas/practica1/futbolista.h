/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
20-sep-2023
*/

#ifndef FUTBOLISTA_H
#define FUTBOLISTA_H

typedef struct {
    char nombre[50];
    char posicion[20];
    int goles;
} Jugador;

typedef struct {
    char nombreEquipo[50];
    int victorias;
    int derrotas;
} Equipo;

typedef struct {
    Jugador jugador;
    Equipo equipo;
} Futbolista;

// Prototipos de funciones
Futbolista* crearFutbolista(const char *nombre, const char *posicion, int goles, const char *nombreEquipo, int victorias, int derrotas);
void destruirFutbolista(Futbolista *futbolista);
void imprimirFutbolista(Futbolista futbolista);
void copiarFutbolista(Futbolista *destino, Futbolista origen);

#endif // FUTBOLISTA_H
