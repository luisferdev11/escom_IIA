#ifndef IMAGEN_BMP_H
#define IMAGEN_BMP_H

#include <vector>
#include <cstdint>
#include <string>

class ImagenBMP {
public:
    ImagenBMP(int ancho, int alto, int bit_count, const std::vector<uint8_t>& pixeles);

    int obtenerAncho() const;
    int obtenerAlto() const;
    int obtenerConteoBits() const;
    const std::vector<uint8_t>& obtenerPixeles() const;

private:
    int ancho;
    int alto;
    int conteo_bits;
    std::vector<uint8_t> pixeles;
};

#endif // IMAGEN_BMP_H 