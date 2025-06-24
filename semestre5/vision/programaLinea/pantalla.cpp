#include "pantalla.h"
#include <iostream>

Pantalla::Pantalla(const std::string& titulo, int ancho, int alto)
    : titulo_(titulo), ancho_(ancho), alto_(alto) {}

Pantalla::~Pantalla() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
    if (ventana_) {
        SDL_DestroyWindow(ventana_);
    }
    SDL_Quit();
    std::cout << "Recursos de Pantalla y SDL liberados." << std::endl;
}

bool Pantalla::inicializar() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    ventana_ = SDL_CreateWindow(titulo_.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                ancho_, alto_,
                                SDL_WINDOW_SHOWN);
    if (!ventana_) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer_ = SDL_CreateRenderer(ventana_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        std::cerr << "Error al crear el renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Pantalla::limpiar() {
    SDL_RenderClear(renderer_);
}

void Pantalla::presentar() {
    SDL_RenderPresent(renderer_);
}

void Pantalla::establecerColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

SDL_Renderer* Pantalla::getRenderer() {
    return renderer_;
} 