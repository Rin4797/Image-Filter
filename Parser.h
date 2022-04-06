#pragma once

#include "filters/FilterFactory.h"
#include "Image.h"
#include "Exception.h"
#include "BMP.h"

#include <exception>
#include <regex>
#include <string>

class Parser {
public:
    Parser();
    void Parse(int argc, const char** argv);
};
