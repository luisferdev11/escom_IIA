#include "bmp.h"
#include <stdexcept>

BMPImage::BMPImage(int32_t width, int32_t height)
    : m_width(width), m_height(height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("El ancho y el alto de la imagen deben ser positivos.");
    }
    m_pixels.resize(width * height);
}

int32_t BMPImage::getWidth() const {
    return m_width;
}

int32_t BMPImage::getHeight() const {
    return m_height;
}

const std::vector<Pixel>& BMPImage::getPixels() const {
    return m_pixels;
}

std::vector<Pixel>& BMPImage::getPixels() {
    return m_pixels;
}

Pixel BMPImage::getPixel(int32_t x, int32_t y) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        throw std::out_of_range("Coordenadas de píxel fuera de rango.");
    }
    return m_pixels[y * m_width + x];
}

void BMPImage::setPixel(int32_t x, int32_t y, Pixel pixel) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        throw std::out_of_range("Coordenadas de píxel fuera de rango.");
    }
    m_pixels[y * m_width + x] = pixel;
} 