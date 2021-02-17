#pragma once
#include <set>
#include "struct.h"
#include "convert.h"

class PixelNode {
    public:
        PixelNode(Position2D pos, ImageSize image_size, float curvature){
            _pos = pos;
            _curvature = curvature;
            _image_size = image_size;
            _hash = position2hash(_pos, _image_size);
        }

    private:
        Position2D _pos;
        ImageSize _image_size;
        int32_t _hash;
        float _curvature;

        int index;
        int rank;
        PixelNode * parent;
        std::set <PixelNode * > children;
        PixelNode(int idx) {
            index = idx;
            rank = 0;
            parent = NULL;
            children.clear();
        }
};