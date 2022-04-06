#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

struct Color {
    uint8_t red = 0, green = 0, blue = 0;

    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);

    Color& operator+=(const Color& other);
    Color& operator-=(const Color& other);
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(const double k) const;
    bool operator==(const Color& other) const;
};

std::ostream& operator<<(std::ostream& out, const Color& color);

class Image {
public:
    void SetColor(int32_t x, int32_t y, const Color& color);
    Color GetColor(int32_t x, int32_t y) const;
    Color GetColorValue(int32_t x, int32_t y) const;
    Image();
    Image(int32_t width, int32_t height);
    Image& operator=(const Image& other);
    void Resize(int32_t width, int32_t height);
    int32_t GetWidth() const;
    int32_t GetHeight() const;

    bool operator==(const Image& other) const;

private:
    int32_t width_;
    int32_t height_;
    std::vector<std::vector<Color> > image_;
};
