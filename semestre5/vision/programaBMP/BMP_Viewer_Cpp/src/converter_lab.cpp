#include "converter_lab.h"
#include <cmath>
#include <algorithm>
#include <vector>

// Constantes de referencia para el iluminante D65
static constexpr float D65_X = 0.95047f;
static constexpr float D65_Y = 1.00000f;
static constexpr float D65_Z = 1.08883f;

// --- Implementación del método principal y el nombre ---
std::unique_ptr<BMPImage> ConverterLab::convert(const BMPImage& image) {
    auto newImage = std::make_unique<BMPImage>(image.getWidth(), image.getHeight());
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);

            float X, Y, Z;
            RGBtoXYZ(p.r, p.g, p.b, X, Y, Z);

            float L, aC, bC;
            XYZtoLab(X, Y, Z, L, aC, bC);

            // Aplicar transformación
            L *= 0.90f;
            aC -= 10.0f;
            bC -= 10.0f;

            LabtoXYZ(L, aC, bC, X, Y, Z);
            
            uint8_t r_new, g_new, b_new;
            XYZtoRGB(X, Y, Z, r_new, g_new, b_new);

            newImage->setPixel(x, y, {b_new, g_new, r_new});
        }
    }
    return newImage;
}

std::string ConverterLab::name() const {
    return "Lab";
}

// --- Funciones auxiliares para la conversión de color ---

static float srgbToLinear(const float c) {
    return (c <= 0.04045f) ? (c / 12.92f) : std::pow((c + 0.055f) / 1.055f, 2.4f);
}

static float linearToSrgb(const float c) {
    return (c <= 0.0031308f) ? (12.92f * c) : (1.055f * std::pow(c, 1.0f / 2.4f) - 0.055f);
}

void ConverterLab::RGBtoXYZ(uint8_t r, uint8_t g, uint8_t b, float& X, float& Y, float& Z) {
    const float rr = srgbToLinear(r / 255.0f);
    const float gg = srgbToLinear(g / 255.0f);
    const float bb = srgbToLinear(b / 255.0f);
    X = rr * 0.4124f + gg * 0.3576f + bb * 0.1805f;
    Y = rr * 0.2126f + gg * 0.7152f + bb * 0.0722f;
    Z = rr * 0.0193f + gg * 0.1192f + bb * 0.9505f;
}

void ConverterLab::XYZtoRGB(float X, float Y, float Z, uint8_t& r, uint8_t& g, uint8_t& b) {
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

static float fLab(const float t) {
    static constexpr float delta = 6.0f / 29.0f;
    if (t > delta * delta * delta) return std::cbrtf(t);
    return t / (3.0f * delta * delta) + 4.0f / 29.0f;
}

static float fLabInv(const float t) {
    static constexpr float delta = 6.0f / 29.0f;
    if (t > delta) return t * t * t;
    return 3.0f * delta * delta * (t - 4.0f / 29.0f);
}

void ConverterLab::XYZtoLab(float X, float Y, float Z, float& L, float& a, float& b) {
    const float xr = X / D65_X;
    const float yr = Y / D65_Y;
    const float zr = Z / D65_Z;
    const float fx = fLab(xr);
    const float fy = fLab(yr);
    const float fz = fLab(zr);
    L = 116.0f * fy - 16.0f;
    a = 500.0f * (fx - fy);
    b = 200.0f * (fy - fz);
}

void ConverterLab::LabtoXYZ(float L, float aC, float bC, float& X, float& Y, float& Z) {
    const float fy = (L + 16.0f) / 116.0f;
    const float fx = fy + aC / 500.0f;
    const float fz = fy - bC / 200.0f;
    const float xr = fLabInv(fx);
    const float yr = fLabInv(fy);
    const float zr = fLabInv(fz);
    X = xr * D65_X;
    Y = yr * D65_Y;
    Z = zr * D65_Z;
} 