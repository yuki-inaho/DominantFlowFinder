#pragma once
#include <set>
#include "struct.h"
#include "convert.h"

class PixelNode {
    public:
        PixelNode(){
            // nothing
        }
        
        PixelNode(Position2D pos, Position2D pos_neighbor_highest_curvature, ImageSize image_size, float curvature){
            _pos = pos;
            _pos_neighbor_highest_curvature = pos_neighbor_highest_curvature;
            _curvature = curvature;
            _image_size = image_size;
            _hash = position2hash(_pos, _image_size); // index = _hash

            rank = 0;
            parent = NULL;
            children.clear();
        }

        bool operator ==(const PixelNode &node) const
        {
            return _curvature == node._curvature;
        }

        bool operator <(const PixelNode &node) const
        {
            return _curvature < node._curvature;
        }

        bool operator >(const PixelNode &node) const
        {
            return _curvature > node._curvature;
        }

        bool operator <=(const PixelNode &node) const
        {
            return _curvature <= node._curvature;
        }

        bool operator >=(const PixelNode &node) const
        {
            return _curvature >= node._curvature;
        }

        size_t hash(){
            return _hash;
        }

        float get_curvature(){
            return _curvature;
        }

        int index;
        int rank;
        PixelNode * parent;
        std::set <PixelNode * > children;

    private:
        Position2D _pos;
        Position2D _pos_neighbor_highest_curvature;
        ImageSize _image_size;
        int32_t _hash;
        float _curvature;

};