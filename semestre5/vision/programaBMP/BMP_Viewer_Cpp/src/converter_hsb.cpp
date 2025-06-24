#include "converter_hsb.h"
#include <algorithm>
#include <cmath>

std::unique_ptr<BMPImage> ConverterHSB::convert(const BMPImage& image) {
    auto newImage = std::make_unique<BMPImage>(image.getWidth(), image.getHeight());

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            
            float h, s, v;
            RGBtoHSB(p.r, p.g, p.b, h, s, v);

            // Aplicar la misma transformación que el proyecto original
            h = fmodf(h + 120.0f, 360.0f);
            s *= 0.75f;

            uint8_t r, g, b;
            HSBtoRGB(h, s, v, r, g, b);
            
            newImage->setPixel(x, y, {b, g, r});
        }
    }
    return newImage;
}

std::string ConverterHSB::name() const {
    return "HSB";
}

void ConverterHSB::RGBtoHSB(uint8_t r, uint8_t g, uint8_t b, float& h, float& s, float& v) {
    float fr = r / 255.0f;
    float fg = g / 255.0f;
    float fb = b / 255.0f;

    const float maxVal = std::max({fr, fg, fb});
    const float minVal = std::min({fr, fg, fb});
    const float delta = maxVal - minVal;

    v = maxVal;
    s = (maxVal == 0.0f) ? 0.0f : (delta / maxVal);

    if (delta < 0.00001f) {
        h = 0.0f;
    } else {
        if (maxVal == fr) {
            h = 60.0f * fmodf(((fg - fb) / delta), 6.0f);
        } else if (maxVal == fg) {
            h = 60.0f * (((fb - fr) / delta) + 2.0f);
        } else {
            h = 60.0f * (((fr - fg) / delta) + 4.0f);
        }
    }

    if (h < 0.0f) {
        h += 360.0f;
    }
}

void ConverterHSB::HSBtoRGB(float h, float s, float v, uint8_t& r, uint8_t& g, uint8_t& b) {
    if (s <= 0.0f) {
        r = g = b = static_cast<uint8_t>(v * 255.0f);
        return;
    }

    const float hh = fmodf(h, 360.0f) / 60.0f;
    const int i = static_cast<int>(hh);
    const float ff = hh - i;

    const float p = v * (1.0f - s);
    const float q = v * (1.0f - (s * ff));
    const float t = v * (1.0f - (s * (1.0f - ff)));

    float nr, ng, nb;
    switch (i) {
        case 0: nr = v; ng = t; nb = p; break;
        case 1: nr = q; ng = v; nb = p; break;
        case 2: nr = p; ng = v; nb = t; break;
        case 3: nr = p; ng = q; nb = v; break;
        case 4: nr = t; ng = p; nb = v; break;
        default: nr = v; ng = p; nb = q; break;
    }

    r = static_cast<uint8_t>(nr * 255.0f);
    g = static_cast<uint8_t>(ng * 255.0f);
    b = static_cast<uint8_t>(nb * 255.0f);
} 