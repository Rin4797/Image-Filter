#include "Parser.h"

#include <iostream>

using namespace std;

int main(int argc, const char** argv) {
    if (argc == 1) {
        std::cout << "USAGE" << std::endl;
        std::cout << "      ./image_processor {path to input} {path to output} [-{filter name 1} [filter's parameter 1] [filter's parameter 2] ...] [-{filter name 2} [filter's parameter 1] [filter's parameter 2] ...] ..." << std::endl;
        std::cout << "FILTERS" << std::endl;
        std::cout << "      -crop, required natural width, height" << std::endl;
        std::cout << "      -gs" << std::endl;
        std::cout << "      -neg" << std::endl;
        std::cout << "      -sharp" << std::endl;
        std::cout << "      -edge, required threshold from 0 to 1" << std::endl;
        std::cout << "      -blur, required sigma" << std::endl;
        std::cout << "      -crys, can recieve crystal size in pix, so crystal size is natural number" << std::endl;
    } else {
        Parser parser;
        parser.Parse(argc, argv);
    }
}