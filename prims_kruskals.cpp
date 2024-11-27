#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <climits> 

using namespace std;

class UnionFind {
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0); 
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    vector<int> parent, rank;
};

struct Edge {
    int u, v, weight;
    bool operator<(const Edge &e) const {
        return weight < e.weight; 
    }
};

int prim(int n, vector<vector<pair<int, int>>>& adj, vector<pair<int, int>>& mstEdges) {
    vector<int> key(n, INT_MAX);
    vector<bool> inMST(n, false); 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0}); 

    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalWeight += key[u];

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                mstEdges.push_back({u, v});
            }
        }
    }

    return totalWeight;
}

int kruskal(int n, vector<Edge>& edges, vector<pair<int, int>>& mstEdges) {
    UnionFind uf(n);
    sort(edges.begin(), edges.end()); 

    int totalWeight = 0;
    for (const auto& edge : edges) {
        int u = edge.u, v = edge.v, weight = edge.weight;
        if (uf.find(u) != uf.find(v)) {
            uf.unionSets(u, v);
            mstEdges.push_back({u, v});
            totalWeight += weight;
        }
    }

    return totalWeight;
}

int main() {
    int n, m; 
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    vector<Edge> edges;

    cout << "Enter edges (u, v, weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        u--; v--;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
        edges.push_back({u, v, weight});
    }

    vector<pair<int, int>> mstEdgesPrim;
    int totalWeightPrim = prim(n, adj, mstEdgesPrim);

    cout << "Total weight of MST using Prim's Algorithm: " << totalWeightPrim << endl;
    cout << "MST edges (Prim's):\n";
    for (auto& edge : mstEdgesPrim) {
        cout << edge.first + 1 << " - " << edge.second + 1 << endl;
    }

    vector<pair<int, int>> mstEdgesKruskal;
    int totalWeightKruskal = kruskal(n, edges, mstEdgesKruskal);

    cout << "Total weight of MST using Kruskal's Algorithm: " << totalWeightKruskal << endl;
    cout << "MST edges (Kruskal's):\n";
    for (auto& edge : mstEdgesKruskal) {
        cout << edge.first + 1 << " - " << edge.second + 1 << endl;
    }

    return 0;
}
// Enter number of nodes and edges: 
// 4 5
// Enter edges (u, v, weight):
// 1 2 10
// 1 3 20
// 2 3 30
// 2 4 40
// 3 4 50
