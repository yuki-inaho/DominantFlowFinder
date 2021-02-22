#include "Graph.h"
#include "gtest/gtest.h"

TEST(GraphTest, AddNode)
{
    Graph G = Graph();
    for (size_t i = 0; i < 10000; i++)
        G.add_node(i);
}

TEST(GraphTest, AddEdge)
{
    Graph G = Graph();
    int32_t n_node = 100;

    std::vector<NodeMock> node_list;

    for (size_t i = 0; i < n_node; i++)
    {
        size_t hash = i;
        float node_attribute = float(i);
        NodeMock node = NodeMock(hash, node_attribute);
        if (i < n_node)
            node.set_parent(hash + 1);
        if (i > 0)
            node.add_children(hash - 1);
        node_list.push_back(node);
    }

    for (size_t i = 0; i < n_node; i++){
        G.add_node(i);
        if(node_list[i].has_parent())
            G.add_edge(i, node_list[i].parent(), node_list);
    }
}
