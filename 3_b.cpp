#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
public:
    int V; // Number of vertices (cities)
    vector<vector<int>> adjMatrix; // Adjacency matrix

    Graph(int V); // Constructor
    void addEdge(int u, int v, int weight); // Function to add an edge
    bool isConnected(); // Function to check if the graph is connected
    void BFS(int start, vector<bool>& visited); // BFS to check connectivity
};

// Constructor
Graph::Graph(int V) {
    this->V = V;
    adjMatrix.resize(V, vector<int>(V, -1)); // Initialize matrix with -1 (no direct flight)
}

// Function to add an edge to the graph
void Graph::addEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight; // Set the edge weight from u to v
    adjMatrix[v][u] = weight; // Set the edge weight from v to u (undirected graph)
}

// Function to perform BFS traversal to check connectivity
void Graph::BFS(int start, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // Visit all the adjacent vertices of the current node
        for (int i = 0; i < V; i++) {
            if (adjMatrix[node][i] != -1 && !visited[i]) { // Check for an edge
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

// Function to check if the graph is connected
bool Graph::isConnected() {
    vector<bool> visited(V, false);

    // Perform BFS starting from vertex 0
    BFS(0, visited);

    // Check if all vertices were visited
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            return false; // Not connected
        }
    }
    return true; // Connected
}

// Main function
int main() {
    int n, e;
    cout << "Enter the number of cities (vertices): ";
    cin >> n;
    Graph g(n); // Create a graph with n cities

    cout << "Enter the number of flight paths (edges): ";
    cin >> e;

    // Take input for edges (flight paths)
    for (int i = 0; i < e; i++) {
        int u, v, weight;
        cout << "Enter the source city (0 to " << n-1 << "), destination city (0 to " << n-1 << "), and flight time/fuel cost: ";
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    // Check if the graph is connected
    if (g.isConnected()) {
        cout << "Graph is connected." << endl;
    } else {
        cout << "Graph is not connected." << endl;
    }

    return 0;
}

// Enter the number of cities (vertices): 5
// Enter the number of flight paths (edges): 4
// Enter the source city (0 to 4), destination city (0 to 4), and flight time/fuel cost: 0 1 10
// Enter the source city (0 to 4), destination city (0 to 4), and flight time/fuel cost: 0 4 20
// Enter the source city (0 to 4), destination city (0 to 4), and flight time/fuel cost: 1 2 30
// Enter the source city (0 to 4), destination city (0 to 4), and flight time/fuel cost: 2 3 40
// Graph is connected.
