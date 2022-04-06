#include "BMP.h"

BMP::BMP() {
}

Image BMP::Import(const char *path) {
    int16_t type;
    int32_t size;
    int32_t offset;
    int32_t header_size;
    int32_t width;
    int32_t height;
    int16_t planes;
    int16_t bit_count;
    int32_t compression;
    int32_t raw_size;
    int32_t h_pix_per_m;
    int32_t v_pix_per_m;
    int32_t used_colors;
    int32_t important_colors;
    Image image_;
    std::ifstream input(path, std::ios::in | std::ios::binary);
    if (input.is_open()) {
        input.read(reinterpret_cast<char *>(&type), sizeof(type));
        input.read(reinterpret_cast<char *>(&size), sizeof(size));
        input.seekg(4, std::ios::cur);
        input.read(reinterpret_cast<char *>(&offset), sizeof(offset));
        input.read(reinterpret_cast<char *>(&header_size), sizeof(header_size));
        input.read(reinterpret_cast<char *>(&width), sizeof(width));
        input.read(reinterpret_cast<char *>(&height), sizeof(height));
        input.read(reinterpret_cast<char *>(&planes), sizeof(planes));
        input.read(reinterpret_cast<char *>(&bit_count), sizeof(bit_count));
        input.read(reinterpret_cast<char *>(&compression), sizeof(compression));
        input.read(reinterpret_cast<char *>(&raw_size), sizeof(raw_size));
        input.read(reinterpret_cast<char *>(&h_pix_per_m), sizeof(h_pix_per_m));
        input.read(reinterpret_cast<char *>(&v_pix_per_m), sizeof(v_pix_per_m));
        input.read(reinterpret_cast<char *>(&used_colors), sizeof(used_colors));
        input.read(reinterpret_cast<char *>(&important_colors), sizeof(important_colors));
        int32_t padding = ((4 - ((width * 3) % 4)) % 4);
        if (type != 0x4d42) {
            throw InvalidBMP("Wrong type");
        }
        if (size != 54 + height * (width * 3 + padding)) {
            throw InvalidBMP("Wrong size");
        }
        if (offset != 54) {
            throw InvalidBMP("Wrong offset");
        }
        if (header_size != 40) {
            throw InvalidBMP("Wrong header size");
        }
        if (planes != 1) {
            throw InvalidBMP("Wrong planes");
        }
        if (bit_count != 24) {
            throw InvalidBMP("Wrong amount of bits");
        }
        if (compression != 0) {
            throw InvalidBMP("Wrong compression");
        }
        if (raw_size != size - 54) {
            throw InvalidBMP("Wrong size of data");
        }
        Color color;
        image_.Resize(width, height);
        try {
            for (int32_t y = 0; y < height; ++y) {
                for (int32_t x = 0; x < width; ++x) {
                    input.read(reinterpret_cast<char *>(&color.blue), sizeof(color.blue));
                    input.read(reinterpret_cast<char *>(&color.green), sizeof(color.green));
                    input.read(reinterpret_cast<char *>(&color.red), sizeof(color.red));
                    image_.SetColor(x, y, color);
                }
                input.seekg(padding, std::ios::cur);
            }
            input.close();
        } catch (...) {
            throw InvalidBMP("Wrong data");
        }
    } else {
        throw InvalidBMP("Cannot be opened for reading");
    }
    return image_;
}

void BMP::Export(const char *path, Image image_) {
    int32_t padding = image_.GetHeight() * (image_.GetWidth() * 3 + ((4 - ((image_.GetWidth() * 3) % 4)) % 4));
    int16_t type = 0x4d42;
    int32_t size = 54 + padding;
    int32_t offset = 54;
    int32_t header_size = 40;
    int32_t width = image_.GetWidth();
    int32_t height = image_.GetHeight();
    int16_t planes = 1;
    int16_t bit_count = 24;
    int32_t compression = 0;
    int32_t raw_size = size - 54;
    int32_t h_pix_per_m = 2835;
    int32_t v_pix_per_m = 2835;
    int32_t used_colors = 0;
    int32_t important_colors = 0;
    std::ofstream output(path, std::ios::out | std::ios::binary);
    if (output.is_open()) {
        output.write("BM", sizeof(type));
        output.write(reinterpret_cast<const char *>(&size), sizeof(size));
        output.write("\0\0\0\0", 4);
        output.write(reinterpret_cast<char *>(&offset), sizeof(offset));
        output.write(reinterpret_cast<char *>(&header_size), sizeof(header_size));

        output.write(reinterpret_cast<char *>(&width), sizeof(width));
        output.write(reinterpret_cast<char *>(&height), sizeof(height));

        output.write(reinterpret_cast<char *>(&planes), sizeof(planes));
        output.write(reinterpret_cast<char *>(&bit_count), sizeof(bit_count));
        output.write(reinterpret_cast<char *>(&compression), sizeof(compression));
        output.write(reinterpret_cast<char *>(&raw_size), sizeof(raw_size));
        output.write(reinterpret_cast<char *>(&h_pix_per_m), sizeof(h_pix_per_m));
        output.write(reinterpret_cast<char *>(&v_pix_per_m), sizeof(v_pix_per_m));
        output.write(reinterpret_cast<char *>(&used_colors), sizeof(used_colors));
        output.write(reinterpret_cast<char *>(&important_colors), sizeof(important_colors));
        uint8_t padding_color = 0;
        size_t padding_size = (4 - ((width * 3) % 4)) % 4;
        for (int32_t y = 0; y < height; ++y) {
            for (int32_t x = 0; x < width; ++x) {
                Color color = image_.GetColor(x, y);
                output.write(reinterpret_cast<char *>(&color.blue), sizeof(color.blue));
                output.write(reinterpret_cast<char *>(&color.green), sizeof(color.green));
                output.write(reinterpret_cast<char *>(&color.red), sizeof(color.red));
            }
            for (size_t id = 0; id < padding_size; ++id) {
                output.write(reinterpret_cast<char *>(&padding_color), sizeof(padding_color));
            }
        }
        output.close();
    } else {
        throw InvalidBMP("Cannot be opened for writing");
    }
}
