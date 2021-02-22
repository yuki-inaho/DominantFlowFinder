#include "Graph.h"
#include "gtest/gtest.h"

TEST(GraphTest, Negative)
{
    Graph G = Graph();
    for (size_t i = 0; i < 10000; i++) G.add_node(i);
    //EXPECT_EQ(1, factorial(-5));
}

