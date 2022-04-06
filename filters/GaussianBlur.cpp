#include "GaussianBlur.h"

#include <cmath>
#include <math.h>
#include <algorithm>
#include <iostream>

GaussianBlur::GaussianBlur() {
}

void GaussianBlur::SetSigma(double sigma) {
    sigma_ = sigma;
}

// Image GaussianBlur::Apply(Image& image) {
//     Image new_image(image.GetWidth(), image.GetHeight());
//     std::vector<std::vector<double> > exp_matrix (static_cast<int>(3 * sigma_ + 2), std::vector<double>
//     (static_cast<int>(3 * sigma_ + 2), 0)); for (int32_t x = 0; x < 3 * sigma_ + 1; ++x) {
//         for (int32_t y = 0; y < 3 * sigma_ + 1; ++y) {
//             long double d_x = static_cast<double>(x);
//             long double d_y = static_cast<double>(y);
//             exp_matrix[x][y] = ((std::exp(-1 * (d_x * d_x + d_y * d_y) / (2 * sigma_ * sigma_))) / sqrt(2 * M_PI) /
//             sigma_);
//         }
//     }
//     for (int32_t x = 0; x < new_image.GetWidth(); ++x) {
//         for (int32_t y = 0; y < new_image.GetHeight(); ++y) {
//             long double new_red = 0;
//             long double new_green = 0;
//             long double new_blue = 0;
//             long double sum_koef = 0;
//             for (int32_t x0 = std::max(0, x - 3 * static_cast<int>(sigma_)); x0 < std::min(new_image.GetWidth(), x +
//             3 * static_cast<int>(sigma_)); ++x0) {
//                 for (int32_t y0 = std::max(0, y - 3 * static_cast<int>(sigma_)); y0 < std::min(new_image.GetHeight(),
//                 y + 3 * static_cast<int>(sigma_)) ; ++y0) {
//                     new_red += (exp_matrix[std::abs(x - x0)][std::abs(y - y0)] * static_cast<long
//                     double>(image.GetColor(x0, y0).red)); new_green += (exp_matrix[std::abs(x - x0)][std::abs(y -
//                     y0)] * static_cast<long double>(image.GetColor(x0, y0).green)); new_blue +=
//                     (exp_matrix[std::abs(x - x0)][std::abs(y - y0)] * static_cast<long double>(image.GetColor(x0,
//                     y0).blue)); sum_koef += exp_matrix[std::abs(x - x0)][std::abs(y - y0)];
//                 }
//             }
//             new_red = new_red / sum_koef;
//             new_green = new_green / sum_koef;
//             new_blue = new_blue / sum_koef;
//             // if (new_red < 0) {new_red = 0;}
//             // else if (new_red > 255) {new_red = 255;}
//             // if (new_green < 0) {new_green = 0;}
//             // else if (new_green > 255) {new_green = 255;}
//             // if (new_blue < 0) {new_blue = 0;}
//             // else if (new_blue > 255) {new_blue = 255;}
//             Color new_color(static_cast<uint8_t>(new_red), static_cast<uint8_t>(new_green),
//             static_cast<uint8_t>(new_blue)); new_image.SetColor(x, y, new_color);
//         }
//     }
//     return new_image;
// }

Image GaussianBlur::Apply(Image& image) {
    Image new_image(image.GetWidth(), image.GetHeight());
    std::vector<double> exp_matrix(static_cast<int>(3 * sigma_ + 3), 0);
    for (int32_t x = 0; x < 3 * sigma_ + 1; ++x) {
        long double d_x = static_cast<double>(x);
        exp_matrix[x] = (std::exp(-1 * d_x * d_x / (2 * sigma_ * sigma_)));
    }
    for (int32_t x = 0; x < new_image.GetWidth(); ++x) {
        for (int32_t y = 0; y < new_image.GetHeight(); ++y) {
            long double new_red = 0;
            long double new_green = 0;
            long double new_blue = 0;
            long double sum_koef = 0;
            for (int32_t x0 = std::max(0, x - 3 * static_cast<int>(sigma_));
                 x0 < std::min(new_image.GetWidth(), x + 3 * static_cast<int>(sigma_) + 1); ++x0) {
                new_red += (exp_matrix[std::abs(x - x0)] * static_cast<long double>(image.GetColor(x0, y).red));
                new_green += (exp_matrix[std::abs(x - x0)] * static_cast<long double>(image.GetColor(x0, y).green));
                new_blue += (exp_matrix[std::abs(x - x0)] * static_cast<long double>(image.GetColor(x0, y).blue));
                sum_koef += exp_matrix[std::abs(x - x0)];
            }
            new_red = new_red / sum_koef;
            new_green = new_green / sum_koef;
            new_blue = new_blue / sum_koef;
            Color new_color(static_cast<uint8_t>(new_red), static_cast<uint8_t>(new_green),
                            static_cast<uint8_t>(new_blue));
            new_image.SetColor(x, y, new_color);
        }
    }
    Image applied_image(image.GetWidth(), image.GetHeight());
    for (int32_t x = 0; x < applied_image.GetWidth(); ++x) {
        for (int32_t y = 0; y < applied_image.GetHeight(); ++y) {
            long double new_red = 0;
            long double new_green = 0;
            long double new_blue = 0;
            long double sum_koef = 0;
            for (int32_t y0 = std::max(0, y - 3 * static_cast<int>(sigma_));
                 y0 < std::min(applied_image.GetWidth(), y + 3 * static_cast<int>(sigma_) + 1); ++y0) {
                new_red += (exp_matrix[std::abs(y - y0)] * static_cast<long double>(new_image.GetColor(x, y0).red));
                new_green += (exp_matrix[std::abs(y - y0)] * static_cast<long double>(new_image.GetColor(x, y0).green));
                new_blue += (exp_matrix[std::abs(y - y0)] * static_cast<long double>(new_image.GetColor(x, y0).blue));
                sum_koef += exp_matrix[std::abs(y - y0)];
            }
            new_red = new_red / sum_koef;
            new_green = new_green / sum_koef;
            new_blue = new_blue / sum_koef;
            Color new_color(static_cast<uint8_t>(new_red), static_cast<uint8_t>(new_green),
                            static_cast<uint8_t>(new_blue));
            applied_image.SetColor(x, y, new_color);
        }
    }
    return applied_image;
}
