/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
20-sep-2023
*/

#include "futbolista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Futbolista *crearFutbolista(const char *nombre, const char *posicion, int goles, const char *nombreEquipo, int victorias, int derrotas) {
    Futbolista *nuevoFutbolista = (Futbolista *)malloc(sizeof(Futbolista));
    if (nuevoFutbolista == NULL) {
        return NULL;
    }
    strcpy(nuevoFutbolista->jugador.nombre, nombre);
    strcpy(nuevoFutbolista->jugador.posicion, posicion);
    nuevoFutbolista->jugador.goles = goles;
    strcpy(nuevoFutbolista->equipo.nombreEquipo, nombreEquipo);
    nuevoFutbolista->equipo.victorias = victorias;
    nuevoFutbolista->equipo.derrotas = derrotas;
    return nuevoFutbolista;
}

void destruirFutbolista(Futbolista *futbolista) {
    futbolista->jugador.nombre[0] = '\0';
    futbolista->jugador.posicion[0] = '\0';
    futbolista->jugador.goles = 0;
    futbolista->equipo.nombreEquipo[0] = '\0';
    futbolista->equipo.victorias = 0;
    futbolista->equipo.derrotas = 0;

    free(futbolista);
}

void imprimirFutbolista(Futbolista futbolista) {
    printf("Jugador: %s, Posición: %s, Goles: %d\n", futbolista.jugador.nombre, futbolista.jugador.posicion, futbolista.jugador.goles);
    printf("Equipo: %s, Victorias: %d, Derrotas: %d\n", futbolista.equipo.nombreEquipo, futbolista.equipo.victorias, futbolista.equipo.derrotas);
}

void copiarFutbolista(Futbolista *destino, Futbolista origen) {
    strcpy(destino->jugador.nombre, origen.jugador.nombre);
    strcpy(destino->jugador.posicion, origen.jugador.posicion);
    destino->jugador.goles = origen.jugador.goles;
    strcpy(destino->equipo.nombreEquipo, origen.equipo.nombreEquipo);
    destino->equipo.victorias = origen.equipo.victorias;
    destino->equipo.derrotas = origen.equipo.derrotas;
}
