#include "../include/imagen_bmp.h"

ImagenBMP::ImagenBMP(int ancho, int alto, int conteo_bits, const std::vector<uint8_t>& pixeles)
    : ancho(ancho), alto(alto), conteo_bits(conteo_bits), pixeles(pixeles) {}

int ImagenBMP::obtenerAncho() const {
    return ancho;
}

int ImagenBMP::obtenerAlto() const {
    return alto;
}

int ImagenBMP::obtenerConteoBits() const {
    return conteo_bits;
}

const std::vector<uint8_t>& ImagenBMP::obtenerPixeles() const {
    return pixeles;
} 