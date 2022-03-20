#pragma once

#include <iostream>
#include <vector>

using std::cerr;
using std::endl;

struct Color {
    uint8_t red, green, blue;

    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);

    Color& operator+=(Color other);
    Color& operator-=(Color other);
    Color operator+(Color other) const;
    Color operator-(Color other) const;
    Color operator*(double k) const;
};

std::ostream& operator<<(std::ostream& out, const Color& color);

class Image {
public:
    void SetColor(int32_t x, int32_t y, Color color);
    Color& GetColor(int32_t x, int32_t y);
    Color GetColorValue(int32_t x, int32_t y) const;
    Image();
    Image(int32_t width, int32_t height);
    Image& operator=(Image other);
    void Resize(int32_t width, int32_t height);
    int32_t GetWidth() const;
    int32_t GetHeight() const;

private:
    int32_t width_;
    int32_t height_;
    std::vector<std::vector<Color> > image_;
};

