#pragma once

#include "Filter.h"

class MatrixFilter : public Filter {
public:
    MatrixFilter();
    MatrixFilter(std::vector<std::vector<int>> c);
    void SetMatrix(std::vector<std::vector<int>> c);
    Image Apply(Image& image);

    ~MatrixFilter() = default;

private:
    std::vector<std::vector<int>> matrix_;
};
