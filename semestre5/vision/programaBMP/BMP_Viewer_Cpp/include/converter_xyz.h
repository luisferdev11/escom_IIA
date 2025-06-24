#ifndef CONVERTER_XYZ_H
#define CONVERTER_XYZ_H

#include "color_converter.h"

class ConverterXYZ : public IColorConverter {
public:
    std::unique_ptr<BMPImage> convert(const BMPImage& image) override;
    std::string name() const override;

private:
    void RGBtoXYZ(uint8_t r, uint8_t g, uint8_t b, float& X, float& Y, float& Z);
    void XYZtoRGB(float X, float Y, float Z, uint8_t& r, uint8_t& g, uint8_t& b);
};

#endif //CONVERTER_XYZ_H 