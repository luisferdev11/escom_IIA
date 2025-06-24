#ifndef RENDERER_H
#define RENDERER_H

#include "bmp.h"
#include <string>
#include <SDL2/SDL.h>

class Renderer {
public:
    void init(int width, int height, const std::string& title);
    void render(const BMPImage& image);
    void waitForClose();
    void close();

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
};

#endif //RENDERER_H 