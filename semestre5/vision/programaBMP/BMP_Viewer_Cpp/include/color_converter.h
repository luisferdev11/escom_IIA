#ifndef ICOLOR_CONVERTER_H
#define ICOLOR_CONVERTER_H

#include "bmp.h"
#include <memory>
#include <string>

class IColorConverter {
public:
    virtual ~IColorConverter() = default;
    virtual std::unique_ptr<BMPImage> convert(const BMPImage& image) = 0;
    virtual std::string name() const = 0;
};

#endif //ICOLOR_CONVERTER_H 