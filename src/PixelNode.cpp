#pragma once

#include "PixelNode.h"

NodeMock::NodeMock(const size_t hash, const float &value)
{
    _hash = hash;
    rank = 0;
    set_parent(_hash);
    children.clear();
}

PixelNode::PixelNode(const Position2D &pos, const Position2D &pos_neighbor_highest_curvature, const ImageSize &image_size, const float &curvature)
{
    _pos = pos;
    _pos_neighbor_highest_curvature = pos_neighbor_highest_curvature;
    _curvature = curvature;
    _image_size = image_size;
    _hash = position2hash(_pos, _image_size); // index = _hash
    _is_extrema = pos == _pos_neighbor_highest_curvature ? true : false;

    rank = 0;
    set_parent(_hash);
    children.clear();
}
