#include "bmp_reader.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cmath>

std::unique_ptr<BMPImage> BMPReader::read(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }

    BMPFileHeader fileHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    if (fileHeader.file_type != 0x4D42) {
        throw std::runtime_error("El archivo no es un BMP válido.");
    }

    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.bit_count != 24 || infoHeader.compression != 0) {
        throw std::runtime_error("Solo se soportan imágenes de 24 bits sin compresión.");
    }

    auto image = std::make_unique<BMPImage>(infoHeader.width, std::abs(infoHeader.height));

    // Mover el puntero del archivo al inicio de los datos de píxeles
    file.seekg(fileHeader.offset_data, std::ios::beg);

    const int32_t width = infoHeader.width;
    const int32_t height = std::abs(infoHeader.height);
    const int padding = (4 - (width * sizeof(Pixel)) % 4) % 4;

    // Los BMP con alto positivo se guardan de abajo hacia arriba.
    bool is_bottom_up = infoHeader.height > 0;

    for (int32_t y = 0; y < height; ++y) {
        int32_t row = is_bottom_up ? (height - 1 - y) : y;
        
        for (int32_t x = 0; x < width; ++x) {
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
            image->setPixel(x, row, pixel);
        }
        // Omitir el padding
        file.seekg(padding, std::ios::cur);
    }

    return image;
} 