#pragma once
#include "Node.h"
#include <vector>
#include <map>
#include <set>
#include <stack>

struct Graph
{
    std::vector<Node *> nodes;
    std::map<int, Node *> M;
    std::set<Node *> intersecting_sets;
    Graph()
    {
        M.clear();
        intersecting_sets.clear();
        nodes.clear();
    }

    Node *get_root(Node *node)
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

    void add_node(int idx)
    {
        nodes.push_back(new Node(idx));
        M[idx] = nodes[nodes.size() - 1];
    }

    void add_edge(int n1, int n2)
    {
        Node *r1 = get_root(M[n1]);
        Node *r2 = get_root(M[n2]);
        if (r1 != r2)
        {
            if (r1->rank > r2->rank)
            {
                r2->parent = r1;
                r1->children.insert(r2);
                if (intersecting_sets.count(r2))
                {
                    intersecting_sets.erase(r2);
                    intersecting_sets.insert(r1);
                }
            }
            else
            {
                r1->parent = r2;
                r2->children.insert(r1);
                if (intersecting_sets.count(r1))
                {
                    intersecting_sets.erase(r1);
                    intersecting_sets.insert(r2);
                }

                if (r1->rank == r2->rank)
                {
                    r2->rank++;
                }
            }
        }
    }

    std::vector<int> get_connected_component(int n)
    {
        Node *r = get_root(M[n]);
        std::vector<int> L;
        std::stack<Node *> s;
        s.push(r);
        while (!s.empty())
        {
            Node *top = s.top();
            s.pop();
            L.push_back(top->index);
            for (std::set<Node *>::iterator it = top->children.begin(); it != top->children.end(); ++it)
            {
                s.push(*it);
            }
        }
        return L;
    }

    bool component_seen(int n)
    {
        Node *r = get_root(M[n]);
        if (intersecting_sets.count(r))
        {
            return true;
        }
        intersecting_sets.insert(r);
        return false;
    }

    int GET_ROOT(int idx)
    {
        Node *r = get_root(M[idx]);
        return r->index;
    }

    std::vector<int> GET_CHILDREN(int idx)
    {
        Node *r = M[idx];
        std::vector<int> to_ret;
        for (std::set<Node *>::iterator it = r->children.begin(); it != r->children.end();++it)
        {
            to_ret.push_back((*it)->index);
        }
        return to_ret;
    }
};
