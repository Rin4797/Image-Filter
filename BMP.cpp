#include "BMP.h"

BMP::BMP() {
    type_ = 0x4d42;
    size_ = 0;
    offset_ = 0;
    header_size_ = 40;
    width_ = 0;
    height_ = 0;
    planes_ = 1;
    bit_count_ = 24;
    compression_ = 0;
    raw_size_ = 16;
    h_pix_per_m_ = 2835;
    v_pix_per_m_ = 2835;
    used_colors_ = 0;
    important_colors_ = 0;
    image_ = Image (0, 0);
}

void BMP::Import(const char *path) {
    std::ifstream input(path, std::ios::in | std::ios::binary);
    if (input.is_open()) {
        input.read(reinterpret_cast<char *>(&type_), sizeof(type_));
        input.read(reinterpret_cast<char *>(&size_), sizeof(size_));
        input.seekg(4, std::ios::cur);
        input.read(reinterpret_cast<char *>(&offset_), sizeof(offset_));
        input.read(reinterpret_cast<char *>(&header_size_), sizeof(header_size_));
        input.read(reinterpret_cast<char *>(&width_), sizeof(width_));
        input.read(reinterpret_cast<char *>(&height_), sizeof(height_));
        std::cerr << "raw " << width_ << ' ' << height_ << std::endl;
        std::cout << "Size: " << size_ << " offset: " << offset_ << " width: " << width_ << " height: " << height_
                  << std::endl;
        std::cout << (4 - (width_ * 3) % 4) % 4 << std::endl;
        input.read(reinterpret_cast<char *>(&planes_), sizeof(planes_));
        input.read(reinterpret_cast<char *>(&bit_count_), sizeof(bit_count_));
        input.read(reinterpret_cast<char *>(&compression_), sizeof(compression_));
        input.read(reinterpret_cast<char *>(&raw_size_), sizeof(raw_size_));
        input.read(reinterpret_cast<char *>(&h_pix_per_m_), sizeof(h_pix_per_m_));
        input.read(reinterpret_cast<char *>(&v_pix_per_m_), sizeof(v_pix_per_m_));
        input.read(reinterpret_cast<char *>(&used_colors_), sizeof(used_colors_));
        input.read(reinterpret_cast<char *>(&important_colors_), sizeof(important_colors_));
        Color color;
        image_ = Image(width_, height_);
        for (int32_t y = 0; y < height_; ++y) {
            for (int32_t x = 0; x < width_; ++x) {
                input.read(reinterpret_cast<char *>(&color.blue), sizeof(color.blue));
                input.read(reinterpret_cast<char *>(&color.green), sizeof(color.green));
                input.read(reinterpret_cast<char *>(&color.red), sizeof(color.red));
                image_.SetColor(x, y, color);
            }
            input.seekg((4 - ((width_ * 3) % 4)) % 4, std::ios::cur);
        }
        input.close();
    }
}

void BMP::Export(const char *path) {
    std::ofstream output(path, std::ios::out | std::ios::binary);
    if (output.is_open()) {
        std::cout << "opened file" << std::endl;
        output.write("BM", sizeof(type_));
        output.write(reinterpret_cast<const char*>(&size_), sizeof(size_));
        output.write("\0\0\0\0", 4);
        output.write(reinterpret_cast<char*>(&offset_), sizeof(offset_));
        output.write(reinterpret_cast<char*>(&header_size_), sizeof(header_size_));

        output.write(reinterpret_cast<char*>(&width_), sizeof(width_));
        output.write(reinterpret_cast<char*>(&height_), sizeof(height_));

        output.write(reinterpret_cast<char*>(&planes_), sizeof(planes_));
        output.write(reinterpret_cast<char*>(&bit_count_), sizeof(bit_count_));
        output.write(reinterpret_cast<char*>(&compression_), sizeof(compression_));
        output.write(reinterpret_cast<char*>(&raw_size_), sizeof(raw_size_));
        output.write(reinterpret_cast<char*>(&h_pix_per_m_), sizeof(h_pix_per_m_));
        output.write(reinterpret_cast<char*>(&v_pix_per_m_), sizeof(v_pix_per_m_));
        output.write(reinterpret_cast<char*>(&used_colors_), sizeof(used_colors_));
        output.write(reinterpret_cast<char*>(&important_colors_), sizeof(important_colors_));
        uint8_t padding_color = 0;
        size_t padding_size = (4 - ((width_ * 3) % 4)) % 4;
        for (int32_t y = 0; y < height_; ++y) {
            for (int32_t x = 0; x < width_; ++x) {
                Color color = image_.GetColor(x, y);
                output.write(reinterpret_cast<char*>(&color.blue), sizeof(color.blue));
                output.write(reinterpret_cast<char*>(&color.green), sizeof(color.green));
                output.write(reinterpret_cast<char*>(&color.red), sizeof(color.red));
            }
            for (size_t id = 0; id < padding_size; ++id) {
                output.write(reinterpret_cast<char*>(&padding_color), sizeof(padding_color));
            }
        }
        output.close();
    }
}

Image BMP::ImportedImage() {
    return image_;
}

void BMP::ImportImage(Image new_image) {
    type_ = 0x4d42;
    size_ = 54 + new_image.GetHeight() * (new_image.GetWidth() * 3 + ((4 - ((new_image.GetWidth() * 3) % 4) % 4)));
    offset_ = 54;
    header_size_ = 40;
    width_ = new_image.GetWidth();
    height_ = new_image.GetHeight();
    planes_ = 1;
    bit_count_ = 24;
    compression_ = 0;
    raw_size_ = size_ - 54;
    h_pix_per_m_ = 2835;
    v_pix_per_m_ = 2835;
    used_colors_ = 0;
    important_colors_ = 0;
    image_ = new_image;
}

std::ostream &operator<<(std::ostream &out, const BMP &bmp) {
    out << "type: " << bmp.type_ << std::endl;
    out << "size: " <<  bmp.size_ << std::endl;
    out << "offset: " << bmp.offset_ << std::endl;
    out << "header_size: " << bmp.header_size_ << std::endl;
    out << "width: " << bmp.width_ << std::endl;
    out << "height: " << bmp.height_ << std::endl;
    out << "planes: " << bmp.planes_ << std::endl;
    out << "bit_count: " << bmp.bit_count_ << std::endl;
    out << "compression: " << bmp.compression_ << std::endl;
    out << "raw_size: " << bmp.raw_size_ << std::endl;
    out << "h_pix_per_m: " << bmp.h_pix_per_m_ << std::endl;
    out << "v_pix_per_m: " << bmp.v_pix_per_m_ << std::endl;
    out << "used_colors: " << bmp.used_colors_ << std::endl;
    out << "important_colors: " << bmp.important_colors_ << std::endl;
    out << "image:" << std::endl;
    for (int32_t y = 0; y < bmp.height_; ++y) {
        for (int32_t x = 0; x < bmp.width_; ++x) {
            out << bmp.image_.GetColorValue(x, y) << "    ";
        }
        out << std::endl;
    }
    return out;
}
