#pragma once

#include "Filter.h"

class Grayscale: public Filter {
public:
    Grayscale();
    Image Apply(Image& image);
};

