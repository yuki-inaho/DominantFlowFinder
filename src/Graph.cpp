
#include "Graph.h"

template <>
NodeHash Graph::get_root(NodeHash hash, std::vector<NodeMock> &node_list)
{
    if (node_list[hash].parent() != UNDEFINED)
    {
        // TODO: simplify
        NodeHash parent_hash = node_list[hash].parent();
        NodeHash root_hash = get_root(parent_hash, node_list);
        node_list[hash].set_parent(root_hash);
        parent_hash = node_list[hash].parent();
        return root_hash;
    }
    else
    {
        return hash;
    }
    return hash;
}

template <>
void Graph::add_edge(NodeHash n1, NodeHash n2, std::vector<NodeMock> &node_list)
{
    NodeHash r1 = get_root(n1, node_list);
    NodeHash r2 = get_root(n2, node_list);

    if (r1 != r2)
    {
        if (node_list[r1].rank > node_list[r2].rank)
        {
            node_list[r2].set_parent(r1);
            node_list[r1].add_children(r2);
        }
        else
        {
            node_list[r1].set_parent(r2);
            node_list[r2].add_children(r1);

            if (node_list[r1].rank == node_list[r2].rank)
            {
                node_list[r2].rank++;
            }
        }
    }
    num_edges = num_edges + 1;
}

template <>
NodeHash Graph::get_root(NodeHash hash, std::vector<PixelNode> &node_list)
{
    if (node_list[hash].parent() != UNDEFINED)
    {
        // TODO: simplify
        NodeHash parent_hash = node_list[hash].parent();
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

template <>
void Graph::add_edge(NodeHash n1, NodeHash n2, std::vector<PixelNode> &node_list)
{
    NodeHash r1 = get_root(n1, node_list);
    NodeHash r2 = get_root(n2, node_list);

    if (r1 != r2)
    {
        if (node_list[r1].rank > node_list[r2].rank)
        {
            node_list[r2].set_parent(r1);
            node_list[r1].add_children(r2);
        }
        else
        {
            node_list[r1].set_parent(r2);
            node_list[r2].add_children(r1);

            if (node_list[r1].rank == node_list[r2].rank)
            {
                node_list[r2].rank++;
            }
        }
    }
    num_edges = num_edges + 1;
}

void Graph::add_node(NodeHash hash)
{
    m_nodes.insert(hash);
    num_nodes = num_nodes + 1;
}
