#pragma once
#include <iostream>

struct Position2D
{
    int32_t x;
    int32_t y;
};

struct ImageSize
{
    int32_t width;
    int32_t height;

    friend std::ostream &operator<<(std::ostream &os, const ImageSize &image_size)
    {
        os << "width:" << image_size.width << " " << "height:" << image_size.height;
        return os;
    };
};