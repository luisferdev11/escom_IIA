#include "converter_cmyk.h"
#include <algorithm>
#include <vector>

std::unique_ptr<BMPImage> ConverterCMYK::convert(const BMPImage& image) {
    auto newImage = std::make_unique<BMPImage>(image.getWidth(), image.getHeight());

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            
            float c, m, yC, k;
            RGBtoCMYK(p.r, p.g, p.b, c, m, yC, k);

            // Aplicar transformación
            k = std::clamp(k + 0.15f, 0.0f, 1.0f);
            c = std::clamp(c * 1.05f, 0.0f, 1.0f);
            m = std::clamp(m * 1.05f, 0.0f, 1.0f);
            yC = std::clamp(yC * 1.05f, 0.0f, 1.0f);

            uint8_t r_new, g_new, b_new;
            CMYKtoRGB(c, m, yC, k, r_new, g_new, b_new);
            
            newImage->setPixel(x, y, {b_new, g_new, r_new});
        }
    }
    return newImage;
}

std::string ConverterCMYK::name() const {
    return "CMYK";
}

void ConverterCMYK::RGBtoCMYK(uint8_t r, uint8_t g, uint8_t b, float& c, float& m, float& y, float& k) {
    float fr = r / 255.f;
    float fg = g / 255.f;
    float fb = b / 255.f;

    k = 1.0f - std::max({fr, fg, fb});
    if (k >= 1.0f - 1e-5f) {
        c = 0.0f;
        m = 0.0f;
        y = 0.0f;
    } else {
        c = (1.0f - fr - k) / (1.0f - k);
        m = (1.0f - fg - k) / (1.0f - k);
        y = (1.0f - fb - k) / (1.0f - k);
    }
}

void ConverterCMYK::CMYKtoRGB(float c, float m, float y, float k, uint8_t& r, uint8_t& g, uint8_t& b) {
    const float fr = (1.0f - c) * (1.0f - k);
    const float fg = (1.0f - m) * (1.0f - k);
    const float fb = (1.0f - y) * (1.0f - k);

    r = static_cast<uint8_t>(fr * 255.f);
    g = static_cast<uint8_t>(fg * 255.f);
    b = static_cast<uint8_t>(fb * 255.f);
} 