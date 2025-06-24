#include "converter_xyz.h"
#include <cmath>
#include <algorithm>
#include <vector>

std::unique_ptr<BMPImage> ConverterXYZ::convert(const BMPImage& image) {
    auto newImage = std::make_unique<BMPImage>(image.getWidth(), image.getHeight());
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);

            float X, Y, Z;
            RGBtoXYZ(p.r, p.g, p.b, X, Y, Z);

            // Aplicar transformación (reducir luminancia)
            Y *= 0.90f;

            uint8_t r_new, g_new, b_new;
            XYZtoRGB(X, Y, Z, r_new, g_new, b_new);

            newImage->setPixel(x, y, {b_new, g_new, r_new});
        }
    }
    return newImage;
}

std::string ConverterXYZ::name() const {
    return "XYZ";
}

// --- Funciones auxiliares de conversión (privadas a esta clase) ---

static float srgbToLinear(const float c) {
    return (c <= 0.04045f) ? (c / 12.92f) : std::pow((c + 0.055f) / 1.055f, 2.4f);
}

static float linearToSrgb(const float c) {
    return (c <= 0.0031308f) ? (12.92f * c) : (1.055f * std::pow(c, 1.0f / 2.4f) - 0.055f);
}

void ConverterXYZ::RGBtoXYZ(uint8_t r, uint8_t g, uint8_t b, float& X, float& Y, float& Z) {
    const float rr = srgbToLinear(r / 255.0f);
    const float gg = srgbToLinear(g / 255.0f);
    const float bb = srgbToLinear(b / 255.0f);
    X = rr * 0.4124f + gg * 0.3576f + bb * 0.1805f;
    Y = rr * 0.2126f + gg * 0.7152f + bb * 0.0722f;
    Z = rr * 0.0193f + gg * 0.1192f + bb * 0.9505f;
}

void ConverterXYZ::XYZtoRGB(float X, float Y, float Z, uint8_t& r, uint8_t& g, uint8_t& b) {
    float rr = X * 3.2406f + Y * -1.5372f + Z * -0.4986f;
    float gg = X * -0.9689f + Y * 1.8758f + Z * 0.0415f;
    float bb = X * 0.0557f + Y * -0.2040f + Z * 1.0570f;

    rr = std::clamp(linearToSrgb(rr), 0.0f, 1.0f);
    gg = std::clamp(linearToSrgb(gg), 0.0f, 1.0f);
    bb = std::clamp(linearToSrgb(bb), 0.0f, 1.0f);

    r = static_cast<uint8_t>(rr * 255.0f);
    g = static_cast<uint8_t>(gg * 255.0f);
    b = static_cast<uint8_t>(bb * 255.0f);
} 