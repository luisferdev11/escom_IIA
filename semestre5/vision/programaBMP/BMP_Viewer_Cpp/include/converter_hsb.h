#ifndef CONVERTER_HSB_H
#define CONVERTER_HSB_H

#include "color_converter.h"

class ConverterHSB : public IColorConverter {
public:
    std::unique_ptr<BMPImage> convert(const BMPImage& image) override;
    std::string name() const override;

private:
    // Helper functions for color space conversion
    void RGBtoHSB(uint8_t r, uint8_t g, uint8_t b, float& h, float& s, float& v);
    void HSBtoRGB(float h, float s, float v, uint8_t& r, uint8_t& g, uint8_t& b);
};

#endif //CONVERTER_HSB_H 