#include "GaussianBlur.h"

#include <cmath>
#include <math.h>

GaussianBlur::GaussianBlur()
{}

void GaussianBlur::SetSigma(float sigma) {
    sigma_ = sigma;
}

Image GaussianBlur::Apply(Image& image) {
    Image new_image(image.GetWidth(), image.GetHeight());
    std::vector<std::vector<float> > exp_matrix (image.GetHeight(), std::vector<float> (image.GetWidth(), 0));
    for (int32_t x = 0; x < image.GetWidth(); ++x) {
        for (int32_t y = 0; y < image.GetHeight(); ++y) {
            long double d_x = static_cast<double>(x);
            long double d_y = static_cast<double>(y);
            exp_matrix[x][y] = std::exp(- (d_x * d_x + d_y * d_y) / 2 / sigma_ / sigma_) / sqrt(2 * M_PI) / sigma_;
        }
    }
    for (int32_t x = 0; x < new_image.GetWidth(); ++x) {
        for (int32_t y = 0; y < new_image.GetHeight(); ++y) {
            long double new_red = 0;
            long double new_green = 0;
            long double new_blue = 0;
            for (int32_t x0 = 0; x0 < new_image.GetWidth(); ++x0) {
                for (int32_t y0 = 0; y0 < new_image.GetHeight(); ++y0) {
                    new_red += exp_matrix[abs(x - x0)][abs(y - y0)] * static_cast<long double>(image.GetColor(x0, y0).red);
                    new_green += exp_matrix[abs(x - x0)][abs(y - y0)] * static_cast<long double>(image.GetColor(x0, y0).green);
                    new_blue += exp_matrix[abs(x - x0)][abs(y - y0)] * static_cast<long double>(image.GetColor(x0, y0).blue);
                }
            }
            std::cout << new_red << " " << new_green << " " << new_blue << std::endl;
            Color new_color(static_cast<uint8_t>(new_red), static_cast<uint8_t>(new_green), static_cast<uint8_t>(new_blue));
            std::cout << new_color << std::endl << std::endl;
            new_image.SetColor(x, y, new_color);
        }
    }
    return new_image;
}
