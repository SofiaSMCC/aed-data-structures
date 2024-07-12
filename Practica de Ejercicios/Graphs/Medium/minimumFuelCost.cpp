#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> adj;
    vector<int> representatives;
    vector<int> seats;

    void dfs(int u, int parent) {
        for (int v : adj[u]) {
            if (v != parent) {
                dfs(v, u);
                // Update number of representatives in city u
                representatives[u] += representatives[v];
            }
        }
    }

    long long minimumFuelCost(vector<vector<int>>& roads, int seats_per_car) {
        int n = roads.size() + 1; // number of cities
        seats.assign(n, seats_per_car);
        adj.resize(n);
        representatives.assign(n, 1); // each city has at least one representative (itself)

        // Build the adjacency list
        for (auto& road : roads) {
            int a = road[0], b = road[1];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // Perform DFS from the capital city (city 0)
        dfs(0, -1); // -1 indicates no parent (start from the capital)

        long long totalFuel = 0;

        // Calculate total fuel cost to bring all representatives to the capital
        for (int i = 1; i < n; ++i) {
            // Total trips required to bring all representatives from city i to the capital
            int trips = (representatives[i] + seats[i] - 1) / seats[i]; // ceiling division
            totalFuel += trips;
        }

        return totalFuel;
    }
};

int main() {
    Solution sol;

    // Example usage:
    vector<vector<int>> roads1 = {{0, 1}, {0, 2}, {0, 3}};
    int seats1 = 5;
    cout << sol.minimumFuelCost(roads1, seats1) << endl; // Output: 3

    vector<vector<int>> roads2 = {{3, 1}, {3, 2}, {1, 0}, {0, 4}, {0, 5}, {4, 6}};
    int seats2 = 2;
    cout << sol.minimumFuelCost(roads2, seats2) << endl; // Output: 7

    vector<vector<int>> roads3 = {};
    int seats3 = 1;
    cout << sol.minimumFuelCost(roads3, seats3) << endl; // Output: 0

    return 0;
}
