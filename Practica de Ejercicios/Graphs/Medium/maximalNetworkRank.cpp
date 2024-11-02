#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maximalNetworkRank(int n, vector<vector<int>> &roads)
    {
        vector<int> degree(n, 0);
        vector<vector<bool>> connected(n, vector<bool>(n, false));

        for (auto road : roads)
        {
            int city1 = road[0];
            int city2 = road[1];
            degree[city1]++;
            degree[city2]++;
            connected[city1][city2] = true;
            connected[city2][city1] = true;
        }

        int maxRank = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int rank = degree[i] + degree[j];
                if (connected[i][j])
                    rank--;
                maxRank = max(maxRank, rank);
            }
        }
        return maxRank;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> roads1 = {{0, 1}, {0, 3}, {1, 2}, {1, 3}};
    vector<vector<int>> roads2 = {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {2, 4}};
    vector<vector<int>> roads3 = {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {5, 6}, {5, 7}};

    cout << sol.maximalNetworkRank(4, roads1) << endl; // Output: 4
    cout << sol.maximalNetworkRank(5, roads2) << endl; // Output: 5
    cout << sol.maximalNetworkRank(8, roads3) << endl; // Output: 5

    return 0;
}
