#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Graph
{
    int V;                  
    vector<vector<int>> dist;

public:
    Graph(int n)
    {
        V = n;
        dist.resize(V, vector<int>(V, numeric_limits<int>::max() / 2));

        for (int i = 0; i < V; ++i)
            dist[i][i] = 0;
    }

    void addEdge(int u, int v, int w)
    {
        dist[u][v] = w;
        dist[v][u] = w; 
    }

    void floydWarshall()
    {
        for (int k = 0; k < V; ++k)
        {
            for (int i = 0; i < V; ++i)
            {
                for (int j = 0; j < V; ++j)
                {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    vector<vector<int>> getDist() const
    {
        return dist;
    }
};

int countReachableCities(const vector<vector<int>> &dist, int V, int threshold)
{
    int minReachableCount = numeric_limits<int>::max();
    int minReachableCity = -1;

    for (int i = 0; i < V; ++i)
    {
        int reachableCount = 0;
        for (int j = 0; j < V; ++j)
        {
            if (i != j && dist[i][j] <= threshold)
                ++reachableCount;
        }

        if (reachableCount < minReachableCount || (reachableCount == minReachableCount && i > minReachableCity))
        {
            minReachableCount = reachableCount;
            minReachableCity = i;
        }
    }
    return minReachableCity;
}

class Solution
{
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
    {
        Graph graph(n);

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            graph.addEdge(u, v, w);
        }

        graph.floydWarshall();

        vector<vector<int>> dist = graph.getDist();
        return countReachableCities(dist, n, distanceThreshold);
    }
};

int main()
{
    Solution sol;

    // Example 1
    int n1 = 4;
    vector<vector<int>> edges1 = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    int distanceThreshold1 = 4;
    cout << "Example 1 Output: " << sol.findTheCity(n1, edges1, distanceThreshold1) << endl;

    // Example 2
    int n2 = 5;
    vector<vector<int>> edges2 = {{0, 1, 2}, {0, 4, 8}, {1, 2, 3}, {1, 4, 2}, {2, 3, 1}, {3, 4, 1}};
    int distanceThreshold2 = 2;
    cout << "Example 2 Output: " << sol.findTheCity(n2, edges2, distanceThreshold2) << endl;

    return 0;
}
