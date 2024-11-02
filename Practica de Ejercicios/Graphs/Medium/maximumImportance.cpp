#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    long long maximumImportance(int n, vector<vector<int>> &roads)
    {
        vector<int> degree(n, 0);
        vector<vector<int>> adj(n);

        // Count degrees and create adjacency list
        for (auto &road : roads)
        {
            int u = road[0], v = road[1];
            degree[u]++;
            degree[v]++;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Pair of (degree, city) and sort by degree in descending order
        vector<pair<int, int>> degreeList;
        for (int i = 0; i < n; ++i)
        {
            degreeList.push_back({degree[i], i});
        }
        sort(degreeList.rbegin(), degreeList.rend());

        // Assign values from highest degree city to lowest degree city
        vector<int> assigned(n, 0);
        int value = n;
        for (auto &[deg, city] : degreeList)
        {
            assigned[city] = value--;
        }

        // Calculate total importance
        long long totalImportance = 0;
        for (auto &road : roads)
        {
            int u = road[0], v = road[1];
            totalImportance += assigned[u] + assigned[v];
        }

        return totalImportance;
    }
};

int main()
{
    Solution sol;
    int n1 = 5;
    vector<vector<int>> roads1 = {{0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {2, 4}};
    cout << sol.maximumImportance(n1, roads1) << endl; // Output: 43

    int n2 = 5;
    vector<vector<int>> roads2 = {{0, 3}, {2, 4}, {1, 3}};
    cout << sol.maximumImportance(n2, roads2) << endl; // Output: 20

    return 0;
}
