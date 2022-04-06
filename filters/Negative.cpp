#include "Negative.h"

Negative::Negative() {
}

Image Negative::Apply(Image& image) {
    Image new_image(image.GetWidth(), image.GetHeight());
    for (int32_t x = 0; x < image.GetWidth(); ++x) {
        for (int32_t y = 0; y < image.GetHeight(); ++y) {
            Color new_color(255 - image.GetColor(x, y).red, 255 - image.GetColor(x, y).green,
                            255 - image.GetColor(x, y).blue);
            new_image.SetColor(x, y, new_color);
        }
    }
    return new_image;
}
