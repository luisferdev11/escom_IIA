#ifndef CONVERTER_LAB_H
#define CONVERTER_LAB_H

#include "color_converter.h"

class ConverterLab : public IColorConverter {
public:
    std::unique_ptr<BMPImage> convert(const BMPImage& image) override;
    std::string name() const override;

private:
    void RGBtoXYZ(uint8_t r, uint8_t g, uint8_t b, float& X, float& Y, float& Z);
    void XYZtoRGB(float X, float Y, float Z, uint8_t& r, uint8_t& g, uint8_t& b);
    void XYZtoLab(float X, float Y, float Z, float& L, float& a, float& b);
    void LabtoXYZ(float L, float a, float b, float& X, float& Y, float& Z);
};

#endif //CONVERTER_LAB_H 