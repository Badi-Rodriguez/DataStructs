#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false; // Already connected (redundant edge)

        // Union by rank
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        return true; // Successful connection
    }
};

int minMovesToConnect(int n, vector<vector<int>>& connections) {
    if (connections.size() < n - 1) return -1; // Not enough edges to connect all nodes

    UnionFind uf(n);
    int redundant = 0;

    for (const auto& edge : connections) {
        if (!uf.unite(edge[0], edge[1])) {
            redundant++; // Count redundant connections
        }
    }

    // Count the number of connected components
    int components = 0;
    for (int i = 0; i < n; ++i) {
        if (uf.find(i) == i) components++;
    }

    // If we have enough redundant edges, we can connect the components
    return (redundant >= components - 1) ? (components - 1) : -1;
}

int main() {
    // Example 1
    int n1 = 4;
    vector<vector<int>> connections1 = {{0, 1}, {0, 2}, {1, 2}};
    cout << "Example 1 Output: " << minMovesToConnect(n1, connections1) << endl;

    // Example 2
    int n2 = 6;
    vector<vector<int>> connections2 = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
    cout << "Example 2 Output: " << minMovesToConnect(n2, connections2) << endl;

    return 0;
}
