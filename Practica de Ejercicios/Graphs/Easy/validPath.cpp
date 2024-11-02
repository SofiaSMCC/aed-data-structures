#include <iostream>
#include <vector>
using namespace std;

class SimplifiedGraph
{
private:
    struct Node
    {
        vector<int> adj;
    };

    vector<Node> nodes;

public:
    SimplifiedGraph(int n)
    {
        nodes.resize(n);
    }

    void addEdge(int u, int v)
    {
        nodes[u].adj.push_back(v);
        nodes[v].adj.push_back(u); // undirected graph
    }

    bool dfs(int current, int destination, vector<bool> &visited)
    {
        if (current == destination)
            return true;
        visited[current] = true;

        for (int neighbor : nodes[current].adj)
        {
            if (!visited[neighbor])
            {
                if (dfs(neighbor, destination, visited))
                    return true;
            }
        }
        return false;
    }

    bool validPath(int source, int destination)
    {
        vector<bool> visited(nodes.size(), false);
        return dfs(source, destination, visited);
    }
};

class Solution
{
public:
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        SimplifiedGraph graph(n);

        for (const auto &edge : edges)
        {
            graph.addEdge(edge[0], edge[1]);
        }

        return graph.validPath(source, destination);
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    cout << solution.validPath(3, edges1, 0, 2) << endl; // Output: true

    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    cout << solution.validPath(6, edges2, 0, 5) << endl; // Output: false

    return 0;
}
