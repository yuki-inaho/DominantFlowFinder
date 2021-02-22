#pragma once

#include <set>
#include <limits>
#include "typedef.h"
#include "struct.h"
#include "convert.h"


class NodeMock
{
public:
    NodeMock()
    {
        // nothing
    }

    /*
    NodeMock(const size_t hash, const float &value)
    {
        _hash = hash;
        rank = 0;
        set_parent(UNDEFINED);
        children.clear();
    }
    */
    NodeMock(const size_t hash, const float &value);

    bool operator==(const NodeMock &node) const
    {
        return _value == node._value;
    }

    bool operator<(const NodeMock &node) const
    {
        return _value < node._value;
    }

    bool operator>(const NodeMock &node) const
    {
        return _value > node._value;
    }

    bool operator<=(const NodeMock &node) const
    {
        return _value <= node._value;
    }

    bool operator>=(const NodeMock &node) const
    {
        return _value >= node._value;
    }

    size_t hash()
    {
        return _hash;
    }

    NodeHash parent()
    {
        if (has_parent())
        {
            return _parent;
        }
        else
        {
            return _hash;
        }
    }

    void set_parent(const NodeHash &parent_hash)
    {
        _parent = parent_hash;
    }

    void add_children(const NodeHash &child_hash)
    {
        children.insert(child_hash);
    }

    bool has_parent()
    {
        return _parent != _hash;
    }

    bool has_children()
    {
        return children.size() > 0;
    }

    int32_t rank;
    std::set<NodeHash> children;

private:
    NodeHash _hash;
    NodeHash _parent;
    float _value;
};

class PixelNode
{
public:
    PixelNode()
    {
        // nothing
    }

    PixelNode(const Position2D &pos, const Position2D &pos_neighbor_highest_curvature, const ImageSize &image_size, const float &curvature);

    bool operator==(const PixelNode &node) const
    {
        return _curvature == node._curvature;
    }

    bool operator<(const PixelNode &node) const
    {
        return _curvature < node._curvature;
    }

    bool operator>(const PixelNode &node) const
    {
        return _curvature > node._curvature;
    }

    bool operator<=(const PixelNode &node) const
    {
        return _curvature <= node._curvature;
    }

    bool operator>=(const PixelNode &node) const
    {
        return _curvature >= node._curvature;
    }

    size_t hash()
    {
        return _hash;
    }

    float get_curvature()
    {
        return _curvature;
    }

    float get_hash_of_neighbor_node_highest_curvature()
    {
        return position2hash(_pos_neighbor_highest_curvature, _image_size);
    }

    bool is_extrema()
    {
        return _is_extrema;
    }

    Position2D position()
    {
        return _pos;
    }

    NodeHash parent()
    {
        if (has_parent())
        {
            return _parent;
        }
        else
        {
            return _hash;
        }
    }

    void set_parent(const NodeHash &parent_hash)
    {
        _parent = parent_hash;
    }

    void add_children(const NodeHash &child_hash)
    {
        children.insert(child_hash);
    }

    bool has_parent()
    {
        return _parent != _hash;
    }

    bool has_children()
    {
        return children.size() > 0;
    }

    int32_t rank;
    std::set<NodeHash> children;
    bool _is_extrema;

private:
    Position2D _pos;
    Position2D _pos_neighbor_highest_curvature;
    ImageSize _image_size;
    NodeHash _hash;
    NodeHash _parent;
    float _curvature;
};