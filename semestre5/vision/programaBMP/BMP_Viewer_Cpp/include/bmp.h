#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <vector>

// Pragma para asegurar que el compilador no agregue padding a las estructuras.
// Es crucial para leer correctamente las cabeceras de archivos binarios.
#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t file_type{0x4D42};    // "BM"
    uint32_t file_size{0};         // Tamaño del archivo en bytes
    uint16_t reserved1{0};         // Reservado, debe ser 0
    uint16_t reserved2{0};         // Reservado, debe ser 0
    uint32_t offset_data{0};       // Offset hasta los datos de los píxeles
};

struct BMPInfoHeader {
    uint32_t size{40};             // Tamaño de esta cabecera
    int32_t width{0};              // Ancho de la imagen
    int32_t height{0};             // Alto de la imagen
    uint16_t planes{1};            // Número de planos, siempre 1
    uint16_t bit_count{24};        // Bits por píxel (usaremos 24)
    uint32_t compression{0};       // Compresión (0=sin compresión)
    uint32_t size_image{0};        // Tamaño de los datos de la imagen
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};

#pragma pack(pop)

// Estructura para representar un píxel de 24 bits (BGR)
struct Pixel {
    uint8_t b{0};
    uint8_t g{0};
    uint8_t r{0};
};

class BMPImage {
public:
    BMPImage(int32_t width, int32_t height);

    int32_t getWidth() const;
    int32_t getHeight() const;
    const std::vector<Pixel>& getPixels() const;
    std::vector<Pixel>& getPixels();

    Pixel getPixel(int32_t x, int32_t y) const;
    void setPixel(int32_t x, int32_t y, Pixel pixel);


private:
    int32_t m_width;
    int32_t m_height;
    std::vector<Pixel> m_pixels;
};

#endif //BMP_H 