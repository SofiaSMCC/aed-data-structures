#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, int &count)
    {
        visited[node] = true;
        count++;
        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
                dfs(neighbor, graph, visited, count);
        }
    }

    long long countPairs(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> graph(n);
        for (auto &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        long long total_pairs = (long long)n * (n - 1) / 2;
        long long reachable_pairs = 0;

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                int count = 0;
                dfs(i, graph, visited, count);
                reachable_pairs += (long long)count * (count - 1) / 2;
            }
        }
        return total_pairs - reachable_pairs;
    }
};

int main()
{
    Solution sol;

    // Example usage
    int n1 = 3;
    vector<vector<int>> edges1 = {{0, 1}, {0, 2}, {1, 2}};
    cout << sol.countPairs(n1, edges1) << endl; // Output: 0

    int n2 = 7;
    vector<vector<int>> edges2 = {{0, 2}, {0, 5}, {2, 4}, {1, 6}, {5, 4}};
    cout << sol.countPairs(n2, edges2) << endl; // Output: 14

    return 0;
}
