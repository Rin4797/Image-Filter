#include "Parser.h"

Parser::Parser()
{}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) {
        ++it;
    }
    return !s.empty() && it == s.end();
}

void Parser::Parse(int argc, const char** argv) {
    if (argc < 3) {
        throw InvalidBMP("Not enough parameters");
    }
    FilterFactory F;
    BMP bmp;
    Image image = bmp.Import(argv[1]);
    for (int id = 3; id < argc; ++id) {
        if (strcmp(argv[id], "-crop") == 0) {
            if (id + 2 < argc) {
                size_t width_check, height_check;
                try {
                    F.crop.SetParameters(std::stoi(argv[id + 1], &width_check), std::stoi(argv[id + 2], &height_check));
                } catch (std::invalid_argument) {
                    throw InvalidFilterArgument("crop argument");
                }
                if (width_check != strlen(argv[id + 1]) || height_check != strlen(argv[id + 2])) {
                    throw InvalidFilterArgument("crop argument");
                }
                image = F.crop.Apply(image);
                id += 2;
            } else {
                throw InvalidFilterArgument("crop argument");
            }
        } else if (strcmp(argv[id], "-gs") == 0) {
            image = F.grayscale.Apply(image);
        } else if (strcmp(argv[id], "-neg") == 0) {
            image = F.negative.Apply(image);
        } else if (strcmp(argv[id], "-sharp") == 0) {
            image = F.sharpening.Apply(image);
        } else if (strcmp(argv[id], "-edge") == 0) {
            if (id + 1 < argc) {
                size_t threshold_check;
                try {
                    F.edge_detection.SetThreshold(std::stod(argv[id + 1], &threshold_check));
                } catch (std::invalid_argument) {
                    throw InvalidFilterArgument("edge argument");
                }
                if (threshold_check != strlen(argv[id + 1])) {
                    throw InvalidFilterArgument("edge argument");
                }
                double threshold = std::stod(argv[id + 1], &threshold_check);
                if (threshold < 0 || threshold > 1) {
                    throw InvalidFilterArgument("edge argument");
                }
                image = F.edge_detection.Apply(image);
                id += 1;
            } else {
                throw InvalidFilterArgument("edge argument");
            }
        } else if (strcmp(argv[id], "-blur") == 0) {
            if (id + 1 < argc) {
                size_t sigma_check;
                try {
                    F.blur.SetSigma(std::stoi(argv[id + 1], &sigma_check));
                } catch (std::invalid_argument) {
                    throw InvalidFilterArgument("blur argument");
                }
                if (sigma_check != strlen(argv[id + 1])) {
                    throw InvalidFilterArgument("blur argument");
                }
                image = F.blur.Apply(image);
                id += 1;
            } else {
                throw InvalidFilterArgument("blur argument");
            }
        } else if (strcmp(argv[id], "-crys") == 0) {
            if (id + 1 < argc && is_number(argv[id + 1])) {
                size_t blocksize_check;
                try {
                    F.crys.SetBlockSize(std::stoi(argv[id + 1], &blocksize_check));
                } catch (std::invalid_argument) {
                    throw InvalidFilterArgument("crys argument");
                }
                if (blocksize_check != strlen(argv[id + 1])) {
                    throw InvalidFilterArgument("crys argument");
                }
                int blocksize = std::stoi(argv[id + 1]);
                if (blocksize <= 0) {
                    throw InvalidFilterArgument("crys argument");
                }
                id += 1;
            }
            image = F.crys.Apply(image);
        } else {
            throw InvalidFilter("Filter is not supported");
        }
    }
    bmp.Export(argv[2], image);
}