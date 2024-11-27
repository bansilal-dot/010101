#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
using namespace std;

class Graph {
public:
    
    int V;

    vector<vector<pair<int, int>>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }
 
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    void dijkstra(int s, int destination) {
        vector<int> dist(V, INT_MAX); 
        vector<int> pred(V, -1);     
        dist[s] = 0; 
        
  
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, s}); 
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto &neighbor : adj[u]) {
                int v = neighbor.first; 
                int weight = neighbor.second;  

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pred[v] = u;  
                    pq.push({dist[v], v}); 
                }
            }
        }
   
        if (dist[destination] == INT_MAX) {
            cout << "Destination city " << destination << " is unreachable from source." << endl;
        } else {
            cout << dist[destination] << endl;

            cout << "Path: ";
            stack<int> path;
            for (int at = destination; at != -1; at = pred[at]) {
                path.push(at);
            }
            
            while (!path.empty()) {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of cities (nodes): ";
    cin >> V;
    
    Graph g(V);
    
    cout << "Enter number of roads (edges): ";
    cin >> E;
    
    cout << "Enter the roads (u, v, weight): " << endl;
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight); 
    }
    
    int source, destination;
    cout << "Enter source city (0 to " << V-1 << "): ";
    cin >> source;
    cout << "Enter destination city (0 to " << V-1 << "): ";
    cin >> destination;
    
    cout << "Shortest path from city " << source << " to city " << destination << " is:" << endl;
    g.dijkstra(source, destination);
    
    return 0;
}

// Enter number of cities (nodes): 5
// Enter number of roads (edges): 7
// Enter the roads (u, v, weight): 
// 0 1 10
// 0 2 5
// 1 2 2
// 1 3 1
// 2 1 3
// 2 3 9
// 3 4 4
// Enter source city (0 to 4): 0
// Enter destination city (0 to 4): 4
