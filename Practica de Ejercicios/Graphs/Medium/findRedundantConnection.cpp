#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int V;                   // Número de vértices
    vector<vector<int>> adj; // Lista de adyacencia

public:
    Graph(int numVertices)
    {
        V = numVertices;
        adj.resize(V + 1); // +1 porque los vértices están numerados de 1 a V
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool hasCycle()
    {
        vector<bool> visited(V + 1, false);
        for (int i = 1; i <= V; ++i)
        {
            if (!visited[i])
            {
                if (dfs(i, -1, visited))
                    return true;
            }
        }
        return false;
    }

private:
    bool dfs(int v, int parent, vector<bool> &visited)
    {
        visited[v] = true;

        for (int neighbor : adj[v])
        {
            if (!visited[neighbor])
            {
                if (dfs(neighbor, v, visited))
                    return true;
            }
            else if (neighbor != parent)
                return true;
        }

        return false;
    }
};

class Solution
{
public:
    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        int n = edges.size();
        Graph graph(n);

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            // Try to add edge (u, v) to the graph
            graph.addEdge(u, v);
            
            // If adding this edge causes a cycle, return it
            if (graph.hasCycle())
                return edge;
        }

        return {}; // No redundant edge found (shouldn't reach here as per problem statement)
    }
};

int main()
{
    Solution solution;

    // Example 1
    vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> result1 = solution.findRedundantConnection(edges1);
    cout << "Example 1: [" << result1[0] << "," << result1[1] << "]" << endl;

    // Example 2
    vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    vector<int> result2 = solution.findRedundantConnection(edges2);
    cout << "Example 2: [" << result2[0] << "," << result2[1] << "]" << endl;

    return 0;
}
