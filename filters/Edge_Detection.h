#pragma once

#include "MatrixFilter.h"
#include "Grayscale.h"

class Edge_Detection: public Filter {
public:
    Edge_Detection();
    Edge_Detection(float threshold);
    void SetThreshold(float threshold);

    Image Apply(Image &image) override;

private:
    MatrixFilter matrix_filter_;
    Grayscale grayscale_;
    uint8_t threshold_;
};

