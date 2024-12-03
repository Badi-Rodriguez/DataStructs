#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Structure to represent a disjoint set (Union-Find)
class DisjointSet {
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find function with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union by rank
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Kruskal's Algorithm function
vector<Edge> kruskal(int nodes, vector<Edge>& edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    vector<Edge> mst;
    DisjointSet ds(nodes);

    for (auto& edge : edges) {
        if (ds.find(edge.source) != ds.find(edge.destination)) {
            mst.push_back(edge);
            ds.unite(edge.source, edge.destination);
        }
    }

    return mst;
}

int main() {
    int nodes = 5;
    vector<Edge> edges = {
            {0, 1, 10}, {0, 3, 30}, {0, 4, 100},
            {1, 2, 50}, {3, 2, 20}, {3, 4, 60},
            {2, 4, 10}
    };

    vector<Edge> mst = kruskal(nodes, edges);

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (auto& edge : mst) {
        cout << edge.source << " -- " << edge.destination << " == " << edge.weight << "\n";
    }

    return 0;
}
