#ifndef LECTOR_BMP_H
#define LECTOR_BMP_H

#include "imagen_bmp.h"
#include <string>
#include <memory>

#pragma pack(push, 1)
struct CabeceraBMP {
    uint16_t tipo;
    uint32_t tamano_archivo;
    uint16_t reservado1;
    uint16_t reservado2;
    uint32_t offset_datos;
    uint32_t tamano_cabecera;
    int32_t  ancho;
    int32_t  alto;
    uint16_t planos;
    uint16_t bit_count;
    uint32_t compresion;
    uint32_t tamano_imagen;
    int32_t  x_pixeles_por_metro;
    int32_t  y_pixeles_por_metro;
    uint32_t colores_usados;
    uint32_t colores_importantes;
};
#pragma pack(pop)

class LectorBMP {
public:
    static std::unique_ptr<ImagenBMP> leerBMP(const std::string& ruta_archivo);
};

#endif // LECTOR_BMP_H 