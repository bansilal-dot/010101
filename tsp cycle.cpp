#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

int tsp(const vector<vector<int>>& graph, int mask, int pos, vector<vector<int>>& dp, int n) {
    if (mask == (1 << n) - 1) {
        return graph[pos][0] == -1 ? INF : graph[pos][0]; // Return to the starting city
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int minCost = INF;

    for (int city = 0; city < n; city++) {
        if (city != pos && (mask & (1 << city)) == 0 && graph[pos][city] != -1) {
            int cost = graph[pos][city] + tsp(graph, mask | (1 << city), city, dp, n);
            minCost = min(minCost, cost);
        }
    }

    dp[mask][pos] = minCost;
    return minCost;
}

int main() {
    vector<vector<int>> tsp = {
        {-1, 10, 15, 20},
        {10, -1, 35, 25},
        {15, 35, -1, 30},
        {20, 25, 30, -1}
    };

    int n = tsp.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    int result = tsp(tsp, 1, 0, dp, n);

    if (result == INF) {
        cout << "No valid TSP cycle exists." << endl;
    } else {
        cout << "The minimum cost in TSP cycle is: " << result << endl;
    }

    return 0;
}
