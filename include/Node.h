#pragma once
#include <set>

struct Node {
    int index;
    int rank;
    Node * parent;
    std::set <Node * > children;
    Node(int idx) {
    	index = idx;
    	rank = 0;
    	parent = NULL;
    	children.clear();
    }

};