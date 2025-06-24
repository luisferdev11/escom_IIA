#include "converter_rgb.h"

std::unique_ptr<BMPImage> ConverterRGB::convert(const BMPImage& image) {
    auto newImage = std::make_unique<BMPImage>(image.getWidth(), image.getHeight());

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            newImage->setPixel(x, y, image.getPixel(x, y));
        }
    }
    return newImage;
}

std::string ConverterRGB::name() const {
    return "RGB (Original)";
} 