#pragma once

#include "Filter.h"

class GaussianBlur: public Filter {
public:
    GaussianBlur();
    void SetSigma(float sigma);
    Image Apply(Image& image) override;

private:
    float sigma_;
};
