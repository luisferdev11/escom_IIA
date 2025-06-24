#include "../include/lector_bmp.h"
#include <fstream>
#include <stdexcept>
#include <vector>

std::unique_ptr<ImagenBMP> LectorBMP::leerBMP(const std::string& ruta_archivo) {
    std::ifstream archivo(ruta_archivo, std::ios::binary);
    if (!archivo) {
        throw std::runtime_error("No se pudo abrir el archivo: " + ruta_archivo);
    }

    CabeceraBMP cabecera;
    archivo.read(reinterpret_cast<char*>(&cabecera), sizeof(CabeceraBMP));

    if (cabecera.tipo != 0x4D42) {
        throw std::runtime_error("El archivo no es un BMP válido.");
    }

    archivo.seekg(cabecera.offset_datos, std::ios::beg);

    const int padding = (4 - (cabecera.ancho * (cabecera.bit_count / 8)) % 4) % 4;
    const int tamano_fila = cabecera.ancho * (cabecera.bit_count / 8) + padding;
    const int tamano_pixeles = tamano_fila * cabecera.alto;
    
    std::vector<uint8_t> datos_pixeles(tamano_pixeles);
    archivo.read(reinterpret_cast<char*>(datos_pixeles.data()), tamano_pixeles);

    return std::make_unique<ImagenBMP>(cabecera.ancho, cabecera.alto, cabecera.bit_count, datos_pixeles);
} 