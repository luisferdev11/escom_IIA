#ifndef PANTALLA_H
#define PANTALLA_H

#include <SDL2/SDL.h>
#include <string>

class Pantalla {
public:
    Pantalla(const std::string& titulo, int ancho, int alto);
    ~Pantalla();

    bool inicializar();
    void limpiar();
    void presentar();
    void establecerColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    SDL_Renderer* getRenderer();

private:
    SDL_Window* ventana_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    std::string titulo_;
    int ancho_;
    int alto_;
};

#endif // PANTALLA_H 