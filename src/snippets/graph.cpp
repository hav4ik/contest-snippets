#include "common.hpp"
#include <gtest/gtest.h>


MACROSNIPPET("head", "graph.snippets", "Graph structures", "Definitions and structures for graph theory")
struct edge {
    edge() = delete;
    edge(int node_to) { to = node_to; }

    /// Destination node id
    int to;
    operator int() const { return to; }
    friend bool operator==(const edge& a, const edge& b) { return a.to == b.to; }
    friend bool operator!=(const edge& a, const edge& b) { return a.to != b.to; }

    /// Additional connection properties (e.g. weight)
    TABSTOP(1)
};
edge invalid_edge(-1);

struct graph {
    graph(int n): g(n) {}
    vector<vector<edge>> g;

    /// Default operations
    edge& add(int a_id, int b_id) {
        if (a_id < 0 || a_id >= g.size() || b_id < 0 || b_id > g.size())
            return invalid_edge;
        g[a_id].push_back(b_id);
        return g[a_id].back();
    }
    void resize(int n) { g.resize(n); }
    vector<edge>& operator[](int i) { return g[i]; }

    /// Additional graph members and properties
    TABSTOP(2)
};
TESTSNIPPET
TEST(GraphStructure, SimpleGraphOperations) {
    graph v(3);
    ASSERT_NE(v.add(0, 1), invalid_edge);
    ASSERT_EQ(v.add(3, 0), invalid_edge);
    v.add(1, 2); v.add(2, 0);
    ASSERT_EQ(1, (int)v[0][0]);
    ASSERT_EQ(2, (int)v[1][0]);
}
ENDMACROSNIPPET
