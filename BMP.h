#pragma once

#include "Image.h"

#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::endl;


class BMP {
public:
    BMP();
    void Export(const char* path);
    void Import(const char* path);
    Image ImportedImage();
    void ImportImage(Image new_image);

    friend std::ostream& operator<<(std::ostream& out, const BMP& bmp);

private:
    int16_t type_;
    int32_t size_;
    int32_t offset_;
    int32_t header_size_;
    int32_t width_;
    int32_t height_;
    int16_t planes_;
    int16_t bit_count_;
    int32_t compression_;
    int32_t raw_size_;
    int32_t h_pix_per_m_;
    int32_t v_pix_per_m_;
    int32_t used_colors_;
    int32_t important_colors_;
    Image image_;

};

std::ostream& operator<<(std::ostream& out, const BMP& bmp);
