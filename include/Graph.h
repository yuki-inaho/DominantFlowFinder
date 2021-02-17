#pragma once
#include "PixelNode.h"
#include <vector>
#include <map>
#include <set>
#include <stack>

// TODO: Use shared pointer

/*
typedef size_t NodeHash;

struct Graph
{
    std::vector<NodeHash> nodes;
    // TODO: rename M so as to more descriptive
    std::map <int32_t, NodeHash> M;
    Graph()
    {
        M.clear();        
        nodes.clear();
    }

    PixelNode *get_root(PixelNode *node)
    {

        if (node->parent != NULL)
        {
            node->parent->children.erase(node);
            node->parent = get_root(node->parent);
            node->parent->children.insert(node);
            return node->parent;
        }
        else
        {
            return node;
        }
    }

    void add_node(NodeHash hash)
    {
        nodes.push_back(new PixelNode(idx));
        M[idx] = nodes[nodes.size() - 1];
    }

    void add_edge(int n1, int n2)
    {
        PixelNode *r1 = get_root(M[n1]);
        PixelNode *r2 = get_root(M[n2]);
        if (r1 != r2)
        {
            if (r1->rank > r2->rank)
            {
                r2->parent = r1;
                r1->children.insert(r2);
            }
            else
            {
                r1->parent = r2;
                r2->children.insert(r1);
                if (r1->rank == r2->rank)
                {
                    r2->rank++;
                }
            }
        }
    }

};
*/