#pragma once
#include <set>

typedef std::pair<int32_t, int32_t> Position2D;

class PixelNode {
    public:
        Position2D pos;
        int32_t hash;
        float curvature;

    private:
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