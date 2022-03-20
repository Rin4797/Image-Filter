#pragma once

#include "Filter.h"

class Crop: public Filter{
public:
    Crop();
    Crop(int32_t height, int32_t width);
    void SetParameters(int32_t width, int32_t height);
    Image Apply(Image& image) override;

private:
    int32_t new_height_;
    int32_t new_width_;
};
