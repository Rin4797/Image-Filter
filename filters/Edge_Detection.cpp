#include "Edge_Detection.h"


Edge_Detection::Edge_Detection(): matrix_filter_(MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}))
{}

Edge_Detection::Edge_Detection(float threshold):
    matrix_filter_(MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}})), threshold_(static_cast<uint8_t>(threshold * 255))
{}

Image Edge_Detection::Apply(Image& image) {
    Image new_image = matrix_filter_.Apply(image);
    new_image = grayscale_.Apply(image);
    Color black(255, 255, 255);
    Color white(0, 0, 0);
    for (int32_t x = 0; x < image.GetWidth(); ++x) {
        for (int32_t y = 0; y < image.GetHeight(); ++y) {
            if (new_image.GetColor(x, y).red > threshold_) {
                new_image.SetColor(x, y, white);
            } else {
                new_image.SetColor(x, y, black);
            }
        }
    }
    return new_image;
}

void Edge_Detection::SetThreshold(float threshold) {
    threshold_ = static_cast<uint8_t>(threshold * 255);
}
