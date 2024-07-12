#include <iostream>
#include <vector>
using namespace std;

class Solution
{
private:
    vector<vector<pair<int, bool>>> graph; 

    void dfs(int node, vector<bool> &visited, int &changeCount)
    {
        visited[node] = true;

        for (auto &neighbor : graph[node])
        {
            int nextNode = neighbor.first;
            bool isOriginalDirection = neighbor.second;

            if (!visited[nextNode])
            {
                if (isOriginalDirection)
                    changeCount++;
                dfs(nextNode, visited, changeCount);
            }
        }
    }

public:
    int minReorder(int n, vector<vector<int>> &connections)
    {
        graph.resize(n);

        for (auto &conn : connections)
        {
            int from = conn[0];
            int to = conn[1];
            graph[from].push_back({to, true});
            graph[to].push_back({from, false});
        }

        vector<bool> visited(n, false);
        int changeCount = 0;
        dfs(0, visited, changeCount);
        return changeCount;
    }
};

int main()
{
    // Example usage:
    int n = 6;
    vector<vector<int>> connections = {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}};

    Solution sol;
    int minChanges = sol.minReorder(n, connections);

    cout << "Minimum changes needed: " << minChanges << endl;

    return 0;
}
