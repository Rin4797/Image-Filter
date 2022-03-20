#pragma once

#include "Filter.h"

class Negative: public Filter {
public:
    Negative();
    Image Apply(Image &image) override;
};
