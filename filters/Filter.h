#pragma once

#include "../Image.h"

using std::cerr;
using std::endl;

class Filter {
public:
    Filter();
    virtual Image Apply(Image& image) = 0;

    ~Filter() = default;

    friend class MatrixFilter;
    friend class Crop;
private:
};
