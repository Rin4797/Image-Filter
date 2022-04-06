#pragma once

#include "Image.h"
#include "Exception.h"

#include <iostream>
#include <fstream>
#include <string>

class BMP {
public:
    BMP();
    void Export(const char* path, Image image);
    Image Import(const char* path);
};
