#include "convert.h"

size_t position2hash(Position2D pos_2d, ImageSize image_size)
{
    size_t hash = pos_2d.y * image_size.width + pos_2d.x;
    return hash;
}
