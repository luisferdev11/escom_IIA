#include "algoritmos_dibujo.h"
#include <cmath>

// Esta función es de bajo nivel y solo la usan los algoritmos de este archivo,
// así que la podemos hacer estática para que no sea visible desde fuera.
static void dibujarPixel(SDL_Renderer* renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void dibujarLinea(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        dibujarPixel(renderer, x0, y0);

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Helper para dibujar los 8 octantes del círculo. También estática.
static void dibujarPuntosCirculo(SDL_Renderer* renderer, int xc, int yc, int x, int y) {
    dibujarPixel(renderer, xc + x, yc + y);
    dibujarPixel(renderer, xc - x, yc + y);
    dibujarPixel(renderer, xc + x, yc - y);
    dibujarPixel(renderer, xc - x, yc - y);
    dibujarPixel(renderer, xc + y, yc + x);
    dibujarPixel(renderer, xc - y, yc + x);
    dibujarPixel(renderer, xc + y, yc - x);
    dibujarPixel(renderer, xc - y, yc - x);
}

void dibujarCirculo(SDL_Renderer* renderer, int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    dibujarPuntosCirculo(renderer, xc, yc, x, y);

    while (y > x) {
        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }
        dibujarPuntosCirculo(renderer, xc, yc, x, y);
    }
} 