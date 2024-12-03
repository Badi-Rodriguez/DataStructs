//
// Created by Badi on 12/3/2024.
//

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int destination, weight;
};

// Structure to compare two nodes in the priority queue
struct Compare {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second; // Min-heap for shortest distance
    }
};

// Dijkstra's Algorithm function
void dijkstra(int start, vector<vector<Edge>>& graph, vector<int>& distances) {
    int n = graph.size();
    distances.assign(n, INT_MAX); // Initialize distances to infinity
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({start, 0}); // Push starting node with distance 0

    while (!pq.empty()) {
        int current = pq.top().first;
        int currentDist = pq.top().second;
        pq.pop();

        // Skip processing if the distance is outdated
        if (currentDist > distances[current])
            continue;

        for (auto& edge : graph[current]) {
            int neighbor = edge.destination;
            int newDist = currentDist + edge.weight;

            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.push({neighbor, newDist});
            }
        }
    }
}

int main() {
    int nodes = 5;
    vector<vector<Edge>> graph(nodes);

    // Sample Graph (directed)
    graph[0] = {{1, 10}, {3, 30}, {4, 100}};
    graph[1] = {{2, 50}};
    graph[2] = {{4, 10}};
    graph[3] = {{2, 20}, {4, 60}};
    graph[4] = {};

    vector<int> distances;
    dijkstra(0, graph, distances);

    cout << "Shortest distances from node 0:\n";
    for (int i = 0; i < nodes; i++) {
        cout << "Node " << i << ": " << distances[i] << "\n";
    }

    return 0;
}
