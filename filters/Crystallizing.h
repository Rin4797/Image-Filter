#pragma once

#include "Filter.h"

#include <vector>
#include <random>

class Crystallizing : public Filter {
public:
    Crystallizing();
    Image Apply(Image& image) override;
    void SetBlockSize(int blocksize);

private:
    int32_t blocksize_;
};