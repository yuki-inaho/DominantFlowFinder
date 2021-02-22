#include <iostream>
#include "Graph.h"
#include "gtest/gtest.h"

TEST(GraphTest, AddNode)
{
    Graph G = Graph();
    for (size_t i = 0; i < 10000; i++)
        G.add_node(i);
}


TEST(GraphTest, AddEdgeSmall)
{
    Graph G = Graph();
    int32_t n_node = 3;

    std::vector<NodeMock> node_list;

    for (size_t i = 0; i < n_node; i++)
    {
        size_t hash = i;
        float node_attribute = float(i);
        NodeMock node = NodeMock(hash, node_attribute);
        if (i < n_node - 1)
            node.set_parent(hash + 1);
        if (i > 0)
            node.add_children(hash - 1);        
        node_list.push_back(node);
    }

    for (size_t i = 0; i < n_node; i++){
        std::cout << "Has " << i << "-th node a parent node? :" <<  node_list[i].has_parent() << std::endl;
        G.add_node(i);
        if(node_list[i].has_parent())
            std::cout << "   index:" << i << " parent:" << node_list[i].parent() << std::endl;
            G.add_edge(i, node_list[i].parent(), node_list);
    }

    std::cout << "num_edges:" << G.num_edges << std::endl;
}

TEST(GraphTest, AddEdgeLarge)
{
    Graph G = Graph();
    int32_t n_node = 100;

    std::vector<NodeMock> node_list;

    for (size_t i = 0; i < n_node; i++)
    {
        size_t hash = i;
        float node_attribute = float(i);
        NodeMock node = NodeMock(hash, node_attribute);
        if (i < n_node - 1)
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

    std::cout << "num_nodes:" << G.num_nodes << std::endl;
    std::cout << "num_edges:" << G.num_edges << std::endl;
}
