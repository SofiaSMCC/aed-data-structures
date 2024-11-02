#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
private:
    vector<vector<int>> adj;
    vector<int> values;

public:
    int maxStarSum(vector<int> &vals, vector<vector<int>> &edges, int k)
    {
        int n = vals.size();
        adj.resize(n);
        values = vals;

        // Build adjacency list
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int maxSum = INT_MIN;

        // Iterate over each node to consider it as a potential center
        for (int i = 0; i < n; ++i)
        {
            int centerValue = values[i];
            vector<int> &neighbors = adj[i];

            // Calculate the sum of the star graph centered at node i
            int starSum = centerValue;
            int numEdges = neighbors.size();

            // Add values of up to k neighbors to the star sum
            for (int j = 0; j < min(k, numEdges); ++j)
            {
                starSum += values[neighbors[j]];
            }

            // Update maximum star sum found
            maxSum = max(maxSum, starSum);
        }

        return maxSum;
    }
};

int main()
{
    Solution sol;
    vector<int> vals1 = {1, 2, 3, 4, 10, -10, -20};
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}, {3, 6}};
    int k1 = 2;

    cout << "Maximum Star Sum: " << sol.maxStarSum(vals1, edges1, k1) << endl; // Output: 16

    return 0;
}
