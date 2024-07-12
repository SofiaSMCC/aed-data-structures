#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adjacencyList;
    vector<bool> visited;

public:
    Graph(int n)
    {
        adjacencyList.resize(n);
        visited.resize(n, false);
    }

    void addEdge(int u, int v)
    {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    void dfs(int node)
    {
        visited[node] = true;
        for (int neighbor : adjacencyList[node])
        {
            if (!visited[neighbor])
                dfs(neighbor);
        }
    }

    int countConnectedComponents()
    {
        int n = adjacencyList.size();
        int count = 0;
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                dfs(i);
                count++;
            }
        }
        return count;
    }
};

class Solution
{
public:
    int removeStones(vector<vector<int>> &stones)
    {
        int n = stones.size();
        Graph graph(n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
                    graph.addEdge(i, j);
            }
        }
        return n - graph.countConnectedComponents();
    }
};

// Test cases
int main()
{
    Solution sol;

    vector<vector<int>> stones1 = {{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}};
    vector<vector<int>> stones2 = {{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}};
    vector<vector<int>> stones3 = {{0, 0}};

    cout << "Output for stones1: " << sol.removeStones(stones1) << endl; // Output: 5
    cout << "Output for stones2: " << sol.removeStones(stones2) << endl; // Output: 3
    cout << "Output for stones3: " << sol.removeStones(stones3) << endl; // Output: 0

    return 0;
}
