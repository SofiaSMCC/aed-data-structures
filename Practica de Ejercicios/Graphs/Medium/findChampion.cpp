#include <iostream>
#include <vector>
using namespace std;

class Graph
{
public:
    vector<vector<int>> adjList;
    vector<int> indegree;
    int n;

    Graph(int vertices) : n(vertices)
    {
        adjList.resize(n);
        indegree.resize(n, 0);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        indegree[v]++;
    }
};

class Solution
{
public:
    int findChampion(int n, vector<vector<int>> &edges)
    {
        Graph graph(n);

        // Build the graph
        for (const auto &edge : edges)
            graph.addEdge(edge[0], edge[1]);

        int champion = -1;

        // Find the node with indegree zero
        for (int i = 0; i < n; ++i)
        {
            if (graph.indegree[i] == 0)
            {
                if (champion == -1)
                    champion = i;
                else
                    // More than one node with indegree zero
                    return -1;
            }
        }

        // If no nodes have indegree zero
        if (champion == -1)
            return -1;
        return champion;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}};
    cout << "Champion: " << solution.findChampion(3, edges1) << endl; // Output: 0

    vector<vector<int>> edges2 = {{0, 2}, {1, 3}, {1, 2}};
    cout << "Champion: " << solution.findChampion(4, edges2) << endl; // Output: -1

    return 0;
}
