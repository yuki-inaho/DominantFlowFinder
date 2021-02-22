#pragma once

#include <vector>
#include <map>
#include <set>
#include <stack>
#include "typedef.h"
#include "PixelNode.h"

class Graph
{
public:
    Graph()
    {
        m_nodes.clear();
    }

    NodeHash get_root(NodeHash hash, std::vector<PixelNode> &node_list);
    void add_node(NodeHash hash);
    void add_edge(NodeHash n1, NodeHash n2, std::vector<PixelNode> &node_list);

    std::set<NodeHash> m_nodes;
};