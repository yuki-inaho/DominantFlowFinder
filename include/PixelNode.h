#pragma once

#include <set>
#include <limits>
#include "typedef.h"
#include "struct.h"
#include "convert.h"

#define UNDEFINED std::numeric_limits<size_t>::max()
class PixelNode {
    public:
        PixelNode(){
            // nothing
        }
        
        PixelNode(const Position2D& pos, const Position2D& pos_neighbor_highest_curvature, const ImageSize& image_size, const float& curvature){
            _pos = pos;
            _pos_neighbor_highest_curvature = pos_neighbor_highest_curvature;
            _curvature = curvature;
            _image_size = image_size;
            _hash = position2hash(_pos, _image_size); // index = _hash

            rank = 0;
            set_parent(UNDEFINED);
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

        float get_hash_of_neighbor_node_highest_curvature(){
            return position2hash(_pos_neighbor_highest_curvature, _image_size);
        }

        bool is_extrema(){
            return _pos == _pos_neighbor_highest_curvature;
        }

        NodeHash parent(){
            return _parent;
        }

        void set_parent(const NodeHash& parent_hash){
            _parent = parent_hash;
        }

        int32_t rank;
        std::set<NodeHash> children;

    private:
        Position2D _pos;
        Position2D _pos_neighbor_highest_curvature;
        ImageSize _image_size;
        NodeHash _hash;
        NodeHash _parent;
        float _curvature;

};