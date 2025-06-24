#ifndef CONVERTER_RGB_H
#define CONVERTER_RGB_H

#include "color_converter.h"

class ConverterRGB : public IColorConverter {
public:
    std::unique_ptr<BMPImage> convert(const BMPImage& image) override;
    std::string name() const override;
};

#endif //CONVERTER_RGB_H 