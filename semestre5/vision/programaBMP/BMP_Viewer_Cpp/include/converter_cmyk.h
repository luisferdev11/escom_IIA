#ifndef CONVERTER_CMYK_H
#define CONVERTER_CMYK_H

#include "color_converter.h"

class ConverterCMYK : public IColorConverter {
public:
    std::unique_ptr<BMPImage> convert(const BMPImage& image) override;
    std::string name() const override;

private:
    void RGBtoCMYK(uint8_t r, uint8_t g, uint8_t b, float& c, float& m, float& y, float& k);
    void CMYKtoRGB(float c, float m, float y, float k, uint8_t& r, uint8_t& g, uint8_t& b);
};

#endif //CONVERTER_CMYK_H 