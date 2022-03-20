#include "Crop.h"

Crop::Crop()
{}

Crop::Crop(int32_t height, int32_t width) {
    new_width_ = width;
    new_height_ = height;
}

Image Crop::Apply(Image& image) {
    Image filtered_image(std::min(image.GetWidth(), new_width_), std::min(image.GetHeight(), new_height_));
    for (int32_t x = 0; x < filtered_image.GetWidth(); ++x) {
        for (int32_t y = 0; y < filtered_image.GetHeight(); ++y) {
            filtered_image.SetColor(x, filtered_image.GetHeight() - 1 - y, image.GetColor( x, image.GetHeight() - 1 - y));
        }
    }
    std::cout << "Crop applied" << std::endl;
    return filtered_image;
}

void Crop::SetParameters(int32_t width, int32_t height) {
    new_width_ = width;
    new_height_ = height;
}
