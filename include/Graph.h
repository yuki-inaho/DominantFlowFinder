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

    template <typename Node>
    NodeHash get_root(NodeHash hash, std::vector<Node> &node_list);
    void add_node(NodeHash hash);
    template <typename Node>
    void add_edge(NodeHash n1, NodeHash n2, std::vector<Node> &node_list);

    std::set<NodeHash> m_nodes;
};