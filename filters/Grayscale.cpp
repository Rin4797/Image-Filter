#include "Grayscale.h"

Grayscale::Grayscale()
{}

Image Grayscale::Apply(Image& image) {
    Image new_image(image.GetWidth(), image.GetHeight());
    for (int32_t x = 0; x < image.GetWidth(); ++x) {
        for (int32_t y = 0; y < image.GetHeight(); ++y) {
            int grey_scale = 0.299 * image.GetColor(x, y).red + 0.587 * image.GetColor(x, y).green +
                             0.114 * image.GetColor(x, y).blue;
            new_image.SetColor(x, y,
                               Color(static_cast<uint8_t>(grey_scale), static_cast<uint8_t>(grey_scale),
                                     static_cast<uint8_t>(grey_scale)));
        }
    }
    return new_image;
}
