#pragma once

#include <vector>
#include <map>
#include <set>
#include <stack>
#include "typedef.h"
#include "PixelNode.h"

// TODO: Use shared pointer

struct Graph
{
    // TODO: rename M so as to more descriptive
    std::set<NodeHash> nodes;
    Graph()
    {
        nodes.clear();
    }

    NodeHash get_root(NodeHash hash, std::vector<PixelNode> &node_list)
    {
        if (node_list[hash].parent() != UNDEFINED)
        {
            // TODO: simplify
            NodeHash parent_hash = node_list[hash].parent();
            //std::cout << hash << " " << parent_hash << std::endl;
            NodeHash root_hash = get_root(parent_hash, node_list);
            node_list[parent_hash].set_parent(root_hash);
            return parent_hash;
        }
        else
        {
            return hash;
        }
       return hash;
    }

    void add_node(NodeHash hash)
    {
        nodes.insert(hash);
    }

    void add_edge(NodeHash n1, NodeHash n2, std::vector<PixelNode> &node_list)
    {
        std::cout << "test3" << std::endl;
        NodeHash r1 = get_root(n1, node_list);
        NodeHash r2 = get_root(n2, node_list);
        //std::cout << "(" << n1 << "," << n2 << ")" << " " << "(" << r1 << "," << r2 << ")" << std::endl;
        std::cout << "test4" << std::endl;

        if (r1 != r2)
        {
            if (node_list[r1].rank > node_list[r2].rank)
            {
                node_list[r2].set_parent(r1);
                //node_list[r1].children.insert(r2);
            }
            else
            {
                node_list[r1].set_parent(r2);
                //node_list[r1].parent = r2;
                //node_list[r2].children.insert(r1);

                if (node_list[r1].rank == node_list[r2].rank)
                {
                    node_list[r2].rank++;
                }
            }
        }
    }
};