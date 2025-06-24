#include "pantalla.h"
#include "algoritmos_dibujo.h"
#include <iostream>

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 600;

int main(int argc, char* argv[]) {
    Pantalla pantalla("Dibujo Modular", ANCHO_PANTALLA, ALTO_PANTALLA);

    if (!pantalla.inicializar()) {
        std::cerr << "Fallo al inicializar la pantalla." << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = pantalla.getRenderer();

    bool corriendo = true;
    SDL_Event evento;
    while (corriendo) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                corriendo = false;
            }
        }

        // 1. Establecer color de fondo y limpiar
        pantalla.establecerColor(0, 0, 0, 255); // Negro
        pantalla.limpiar();

        // 2. Establecer color de dibujo
        pantalla.establecerColor(255, 255, 255, 255); // Blanco

        // 3. Dibujar las formas usando los algoritmos
        dibujarLinea(renderer, 50, 50, 750, 550);
        dibujarCirculo(renderer, ANCHO_PANTALLA / 2, ALTO_PANTALLA / 2, 200);

        // 4. Mostrar el resultado
        pantalla.presentar();
    }

    return 0;
} 