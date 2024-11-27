#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
public:
    int V; 
    vector<vector<int>> adjMatrix;
    Graph(int V); 
    void addEdge(int u, int v, int weight); 
    bool isConnected(); 
    void BFS(int start, vector<bool>& visited); 
};

Graph::Graph(int V) {
    this->V = V;
    adjMatrix.resize(V, vector<int>(V, -1)); 
}

void Graph::addEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight; 
    adjMatrix[v][u] = weight; 
}

void Graph::BFS(int start, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int i = 0; i < V; i++) {
            if (adjMatrix[node][i] != -1 && !visited[i]) { 
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

bool Graph::isConnected() {
    vector<bool> visited(V, false);

    BFS(0, visited);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            return false; 
        }
    }
    return true; 
}

int main() {
    int n, e;
    cout << "Enter the number of cities (vertices): ";
    cin >> n;
    Graph g(n);

    cout << "Enter the number of flight paths (edges): ";
    cin >> e;

   
    for (int i = 0; i < e; i++) {
        int u, v, weight;
        cout << "Enter the source city (0 to " << n-1 << "), destination city (0 to " << n-1 << "), and flight time/fuel cost: ";
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

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
