#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// Function to perform DFS
void dfs(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> s;
    s.push(start);

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (!visited[current]) {
            cout << current << " ";
            visited[current] = true;

            // Push unvisited neighbors to the stack (reverse order for consistent traversal)
            for (auto it = graph[current].rbegin(); it != graph[current].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
    }
    cout << endl;
}

// Function to perform BFS
void bfs(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";

        // Enqueue unvisited neighbors
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    // Graph represented as an adjacency list
    int nodes = 6;
    vector<vector<int>> graph = {
            {1, 2},        // Node 0
            {0, 3, 4},     // Node 1
            {0, 4},        // Node 2
            {1, 5},        // Node 3
            {1, 2, 5},     // Node 4
            {3, 4}         // Node 5
    };

    // Perform DFS
    vector<bool> visitedDFS(nodes, false);
    dfs(0, graph, visitedDFS);

    // Perform BFS
    vector<bool> visitedBFS(nodes, false);
    bfs(0, graph, visitedBFS);

    return 0;
}
