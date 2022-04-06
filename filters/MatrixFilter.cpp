#include "MatrixFilter.h"

MatrixFilter::MatrixFilter() : Filter(), matrix_(std::vector<std::vector<int>>(3, std::vector(3, 0))) {
}

MatrixFilter::MatrixFilter(std::vector<std::vector<int>> c) {
    matrix_ = (c);
}

Image MatrixFilter::Apply(Image& image) {
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    Image filtered_image(width, height);
    for (int32_t x = 0; x < width; ++x) {
        for (int32_t y = 0; y < height; ++y) {
            int new_red = 0, new_green = 0, new_blue = 0;
            new_red =
                std::min(255, std::max(matrix_[0][0] * static_cast<int>(image.GetColorValue(x - 1, y - 1).red) +
                                           matrix_[0][1] * static_cast<int>(image.GetColorValue(x - 1, y).red) +
                                           matrix_[0][2] * static_cast<int>(image.GetColorValue(x - 1, y + 1).red) +
                                           matrix_[1][0] * static_cast<int>(image.GetColorValue(x, y - 1).red) +
                                           matrix_[1][1] * static_cast<int>(image.GetColorValue(x, y).red) +
                                           matrix_[1][2] * static_cast<int>(image.GetColorValue(x, y + 1).red) +
                                           matrix_[2][0] * static_cast<int>(image.GetColorValue(x + 1, y - 1).red) +
                                           matrix_[2][1] * static_cast<int>(image.GetColorValue(x + 1, y).red) +
                                           matrix_[2][2] * static_cast<int>(image.GetColorValue(x + 1, y + 1).red),
                                       0));
            new_green =
                std::min(255, std::max(matrix_[0][0] * static_cast<int>(image.GetColorValue(x - 1, y - 1).green) +
                                           matrix_[0][1] * static_cast<int>(image.GetColorValue(x - 1, y).green) +
                                           matrix_[0][2] * static_cast<int>(image.GetColorValue(x - 1, y + 1).green) +
                                           matrix_[1][0] * static_cast<int>(image.GetColorValue(x, y - 1).green) +
                                           matrix_[1][1] * static_cast<int>(image.GetColorValue(x, y).green) +
                                           matrix_[1][2] * static_cast<int>(image.GetColorValue(x, y + 1).green) +
                                           matrix_[2][0] * static_cast<int>(image.GetColorValue(x + 1, y - 1).green) +
                                           matrix_[2][1] * static_cast<int>(image.GetColorValue(x + 1, y).green) +
                                           matrix_[2][2] * static_cast<int>(image.GetColorValue(x + 1, y + 1).green),
                                       0));
            new_blue =
                std::min(255, std::max(matrix_[0][0] * static_cast<int>(image.GetColorValue(x - 1, y - 1).blue) +
                                           matrix_[0][1] * static_cast<int>(image.GetColorValue(x - 1, y).blue) +
                                           matrix_[0][2] * static_cast<int>(image.GetColorValue(x - 1, y + 1).blue) +
                                           matrix_[1][0] * static_cast<int>(image.GetColorValue(x, y - 1).blue) +
                                           matrix_[1][1] * static_cast<int>(image.GetColorValue(x, y).blue) +
                                           matrix_[1][2] * static_cast<int>(image.GetColorValue(x, y + 1).blue) +
                                           matrix_[2][0] * static_cast<int>(image.GetColorValue(x + 1, y - 1).blue) +
                                           matrix_[2][1] * static_cast<int>(image.GetColorValue(x + 1, y).blue) +
                                           matrix_[2][2] * static_cast<int>(image.GetColorValue(x + 1, y + 1).blue),
                                       0));
            filtered_image.SetColor(
                x, y,
                Color(static_cast<uint8_t>(new_red), static_cast<uint8_t>(new_green), static_cast<uint8_t>(new_blue)));
        }
    }
    return filtered_image;
}

void MatrixFilter::SetMatrix(std::vector<std::vector<int>> c) {
    matrix_ = std::move(c);
}
