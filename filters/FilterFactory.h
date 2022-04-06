#pragma once

#include "Filter.h"
#include "MatrixFilter.h"
#include "Sharpening.h"
#include "Edge_Detection.h"
#include "Crop.h"
#include "Grayscale.h"
#include "Negative.h"
#include "GaussianBlur.h"
#include "Crystallizing.h"

struct FilterFactory {
    MatrixFilter matrix_filter;
    Sharpening sharpening;
    Edge_Detection edge_detection;
    Crop crop;
    Grayscale grayscale;
    Negative negative;
    GaussianBlur blur;
    Crystallizing crys;
};
