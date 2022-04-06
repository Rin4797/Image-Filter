#pragma once

#include "Filter.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur();
    void SetSigma(double sigma);
    Image Apply(Image& image) override;

private:
    double sigma_;
};
