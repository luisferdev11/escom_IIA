#ifndef ALGORITMOS_DIBUJO_H
#define ALGORITMOS_DIBUJO_H

#include <SDL2/SDL.h>

// Dibuja una línea usando el algoritmo de Bresenham
void dibujarLinea(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);

// Dibuja un círculo usando el algoritmo de punto medio
void dibujarCirculo(SDL_Renderer* renderer, int xc, int yc, int r);

#endif // ALGORITMOS_DIBUJO_H 