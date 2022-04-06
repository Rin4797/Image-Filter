#include "Crystallizing.h"

#include <iostream>

Crystallizing::Crystallizing() {
    blocksize_ = 10;
}

void Crystallizing::SetBlockSize(int blocksize) {
    blocksize_ = std::move(blocksize);
}

Image Crystallizing::Apply(Image& image) {
    int32_t centers_width = (image.GetWidth() + blocksize_ - 1) / blocksize_;
    int32_t centers_height = (image.GetHeight() + blocksize_ - 1) / blocksize_;
    std::vector<std::vector<int32_t> > centers_x(centers_width, std::vector<int32_t>(centers_height, 0));
    std::vector<std::vector<int32_t> > centers_y(centers_width, std::vector<int32_t>(centers_height, 0));

    for (int32_t x = 0; x < centers_width; ++x) {
        for (int32_t y = 0; y < centers_height; ++y) {
            centers_x[x][y] = std::min(rand() % blocksize_ + blocksize_ * x, image.GetWidth() - 1);
            centers_y[x][y] = std::min(rand() % blocksize_ + blocksize_ * y, image.GetHeight() - 1);
        }
    }

    Image new_image(image.GetWidth(), image.GetHeight());

    for (int32_t x = 0; x < image.GetWidth(); ++x) {
        for (int32_t y = 0; y < image.GetHeight(); ++y) {
            int32_t distance = 8 * blocksize_ * blocksize_;
            int32_t block_x = x / blocksize_;
            int32_t block_y = y / blocksize_;
            if (block_x > 0 && block_y > 0 &&
                distance > (x - centers_x[block_x - 1][block_y - 1]) * (x - centers_x[block_x - 1][block_y - 1]) +
                               (y - centers_y[block_x - 1][block_y - 1]) * (y - centers_y[block_x - 1][block_y - 1])) {
                distance = (x - centers_x[block_x - 1][block_y - 1]) * (x - centers_x[block_x - 1][block_y - 1]) +
                           (y - centers_y[block_x - 1][block_y - 1]) * (y - centers_y[block_x - 1][block_y - 1]);
                new_image.SetColor(
                    x, y, image.GetColor(centers_x[block_x - 1][block_y - 1], centers_y[block_x - 1][block_y - 1]));
            }
            if (block_x > 0 &&
                distance > (x - centers_x[block_x - 1][block_y]) * (x - centers_x[block_x - 1][block_y]) +
                               (y - centers_y[block_x - 1][block_y]) * (y - centers_y[block_x - 1][block_y])) {
                distance = (x - centers_x[block_x - 1][block_y]) * (x - centers_x[block_x - 1][block_y]) +
                           (y - centers_y[block_x - 1][block_y]) * (y - centers_y[block_x - 1][block_y]);
                new_image.SetColor(x, y,
                                   image.GetColor(centers_x[block_x - 1][block_y], centers_y[block_x - 1][block_y]));
            }
            if (block_y > 0 &&
                distance > (x - centers_x[block_x][block_y - 1]) * (x - centers_x[block_x][block_y - 1]) +
                               (y - centers_y[block_x][block_y - 1]) * (y - centers_y[block_x][block_y - 1])) {
                distance = (x - centers_x[block_x][block_y - 1]) * (x - centers_x[block_x][block_y - 1]) +
                           (y - centers_y[block_x][block_y - 1]) * (y - centers_y[block_x][block_y - 1]);
                new_image.SetColor(x, y,
                                   image.GetColor(centers_x[block_x][block_y - 1], centers_y[block_x][block_y - 1]));
            }
            if (block_x > 0 && block_y < (centers_height - 1) &&
                distance > (x - centers_x[block_x - 1][block_y + 1]) * (x - centers_x[block_x - 1][block_y + 1]) +
                               (y - centers_y[block_x - 1][block_y + 1]) * (y - centers_y[block_x - 1][block_y + 1])) {
                distance = (x - centers_x[block_x - 1][block_y + 1]) * (x - centers_x[block_x - 1][block_y + 1]) +
                           (y - centers_y[block_x - 1][block_y + 1]) * (y - centers_y[block_x - 1][block_y + 1]);
                new_image.SetColor(
                    x, y, image.GetColor(centers_x[block_x - 1][block_y + 1], centers_y[block_x - 1][block_y + 1]));
            }
            if (block_x < (centers_width - 1) && block_y > 0 &&
                distance > (x - centers_x[block_x + 1][block_y - 1]) * (x - centers_x[block_x + 1][block_y - 1]) +
                               (y - centers_y[block_x + 1][block_y - 1]) * (y - centers_y[block_x + 1][block_y - 1])) {
                distance = (x - centers_x[block_x + 1][block_y - 1]) * (x - centers_x[block_x + 1][block_y - 1]) +
                           (y - centers_y[block_x + 1][block_y - 1]) * (y - centers_y[block_x + 1][block_y - 1]);
                new_image.SetColor(
                    x, y, image.GetColor(centers_x[block_x + 1][block_y - 1], centers_y[block_x + 1][block_y - 1]));
            }
            if (block_x < (centers_width - 1) && block_y < (centers_height - 1) &&
                distance > (x - centers_x[block_x + 1][block_y + 1]) * (x - centers_x[block_x + 1][block_y + 1]) +
                               (y - centers_y[block_x + 1][block_y + 1]) * (y - centers_y[block_x + 1][block_y + 1])) {
                distance = (x - centers_x[block_x + 1][block_y + 1]) * (x - centers_x[block_x + 1][block_y + 1]) +
                           (y - centers_y[block_x + 1][block_y + 1]) * (y - centers_y[block_x + 1][block_y + 1]);
                new_image.SetColor(
                    x, y, image.GetColor(centers_x[block_x + 1][block_y + 1], centers_y[block_x + 1][block_y + 1]));
            }
            if (block_x < (centers_width - 1) &&
                distance > (x - centers_x[block_x + 1][block_y]) * (x - centers_x[block_x + 1][block_y]) +
                               (y - centers_y[block_x + 1][block_y]) * (y - centers_y[block_x + 1][block_y])) {
                distance = (x - centers_x[block_x + 1][block_y]) * (x - centers_x[block_x + 1][block_y]) +
                           (y - centers_y[block_x + 1][block_y]) * (y - centers_y[block_x + 1][block_y]);
                new_image.SetColor(x, y,
                                   image.GetColor(centers_x[block_x + 1][block_y], centers_y[block_x + 1][block_y]));
            }
            if (block_y < (centers_height - 1) &&
                distance > (x - centers_x[block_x][block_y + 1]) * (x - centers_x[block_x][block_y + 1]) +
                               (y - centers_y[block_x][block_y + 1]) * (y - centers_y[block_x][block_y + 1])) {
                distance = (x - centers_x[block_x][block_y + 1]) * (x - centers_x[block_x][block_y + 1]) +
                           (y - centers_y[block_x][block_y + 1]) * (y - centers_y[block_x][block_y + 1]);
                new_image.SetColor(x, y,
                                   image.GetColor(centers_x[block_x][block_y + 1], centers_y[block_x][block_y + 1]));
            }
            if (distance > (x - centers_x[block_x][block_y]) * (x - centers_x[block_x][block_y]) +
                               (y - centers_y[block_x][block_y]) * (y - centers_y[block_x][block_y])) {
                distance = (x - centers_x[block_x][block_y]) * (x - centers_x[block_x][block_y]) +
                           (y - centers_y[block_x][block_y]) * (y - centers_y[block_x][block_y]);
                new_image.SetColor(x, y, image.GetColor(centers_x[block_x][block_y], centers_y[block_x][block_y]));
            }
        }
    }
    return new_image;
}