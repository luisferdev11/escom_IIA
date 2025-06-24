#include "renderer.h"
#include <stdexcept>

void Renderer::init(int width, int height, const std::string& title) {
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!m_window) {
        throw std::runtime_error(std::string("Error al crear la ventana: ") + SDL_GetError());
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        throw std::runtime_error(std::string("Error al crear el renderer: ") + SDL_GetError());
    }
}

void Renderer::close() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Renderer::render(const BMPImage& image) {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            SDL_SetRenderDrawColor(m_renderer, p.r, p.g, p.b, 255);
            SDL_RenderDrawPoint(m_renderer, x, y);
        }
    }

    SDL_RenderPresent(m_renderer);
}

void Renderer::waitForClose() {
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
} 