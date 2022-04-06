#include "Image.h"

Color::Color() : red(0), green(0), blue(0)
{}

Color::Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b)
{}

Color& Color::operator+=(const Color& other) {
    red = std::min(255, std::max(0, red + other.red));
    green = std::min(255, std::max(0, green + other.green));
    blue = std::min(255, std::max(0, blue + other.blue));
    return *this;
}

Color& Color::operator-=(const Color& other) {
    red = std::min(255, std::max(0, red - other.red));
    green = std::min(255, std::max(0, green - other.green));
    blue = std::min(255, std::max(0, blue - other.blue));
    return *this;
}

Color Color::operator+(const Color& other) const {
    Color new_color(red, green, blue);
    new_color += other;
    return new_color;
}

Color Color::operator-(const Color& other) const {
    Color new_color(red, green, blue);
    new_color -= other;
    return new_color;
}

Color Color::operator*(const double koef) const {
    Color new_color;
    new_color.red = static_cast<uint8_t>(static_cast<double>(red) * koef);
    new_color.green = static_cast<uint8_t>(static_cast<double>(green) * koef);
    new_color.blue = static_cast<uint8_t>(static_cast<double>(blue) * koef);
    return new_color;
}

bool Color::operator==(const Color& other) const {
    return (red == other.red) && (blue == other.blue) && (green == other.green);
}

Image::Image(int32_t width, int32_t height) : width_(width), height_(height) {
    image_ = std::vector<std::vector<Color> >(width, std::vector<Color>(height, Color()));
}

Image::Image() : width_(0), height_(0) {
    image_ = std::vector<std::vector<Color> >(0, std::vector<Color>(0, Color()));
}

void Image::SetColor(int32_t x, int32_t y, const Color& color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }
    image_[x][y] = color;
}

Color Image::GetColor(int32_t x, int32_t y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        throw std::out_of_range("Wrong coordinates");
    }
    return image_[x][y];
}

Color Image::GetColorValue(int32_t x, int32_t y) const {
    int32_t d_x = x;
    int32_t d_y = y;
    if (x < 0) {
        d_x = 0;
    } else if (x >= width_) {
        d_x = width_ - 1;
    }
    if (y < 0) {
        d_y = 0;
    } else if (y >= height_) {
        d_y = height_ - 1;
    }
    return image_[d_x][d_y];
}

int32_t Image::GetWidth() const {
    return width_;
}

int32_t Image::GetHeight() const {
    return height_;
}

void Image::Resize(int32_t width, int32_t height) {
    width_ = width;
    height_ = height;
    image_ = std::vector<std::vector<Color> >(width_, std::vector(height_, Color()));
}

Image& Image::operator=(const Image& other) {
    image_ = other.image_;
    height_ = other.height_;
    width_ = other.width_;
    return *this;
}

bool Image::operator==(const Image& other) const {
    if (width_ != other.GetWidth() || height_ != other.GetHeight()) {
        return false;
    }
    for (int32_t x = 0; x < width_; ++x) {
        for (int32_t y = 0; y < height_; ++y) {
            if (image_[x][y] != other.GetColor(x, y)) {
                return false;
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const Color& color) {
    out << static_cast<size_t>(color.red) << " " << static_cast<size_t>(color.green) << " "
        << static_cast<size_t>(color.blue);
    return out;
}
