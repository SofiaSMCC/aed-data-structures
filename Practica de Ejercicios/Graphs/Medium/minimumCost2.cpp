#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Graph
{
public:
    vector<vector<pair<int, long long>>> adjList;
    int n;

    Graph(int vertices) : n(vertices)
    {
        adjList.resize(n);
    }

    void addEdge(int u, int v, long long cost)
    {
        adjList[u].emplace_back(v, cost);
    }

    vector<vector<long long>> floydWarshall()
    {
        vector<vector<long long>> dist(n, vector<long long>(n, LLONG_MAX));

        // Initialize the distance matrix
        for (int i = 0; i < n; ++i)
        {
            dist[i][i] = 0;
        }

        // Fill initial distances from the adjacency list
        for (int u = 0; u < n; ++u)
        {
            for (const auto &[v, cost] : adjList[u])
            {
                dist[u][v] = min(dist[u][v], cost);
            }
        }

        // Floyd-Warshall algorithm
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX)
                    {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        return dist;
    }
};

class Solution
{
public:
    long long minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost)
    {
        int alphabetSize = 26; // There are 26 lowercase English letters
        Graph graph(alphabetSize);

        // Build the graph
        for (int i = 0; i < original.size(); ++i)
        {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            graph.addEdge(u, v, cost[i]);
        }

        // Run Floyd-Warshall algorithm to find all-pairs shortest paths
        vector<vector<long long>> dist = graph.floydWarshall();

        long long totalCost = 0;
        for (int i = 0; i < source.size(); ++i)
        {
            if (source[i] == target[i])
                continue;
            int u = source[i] - 'a';
            int v = target[i] - 'a';
            if (dist[u][v] == LLONG_MAX)
            {
                return -1; // Conversion is not possible
            }
            totalCost += dist[u][v];
        }

        return totalCost;
    }
};

int main()
{
    Solution solution;

    // Test case 1
    string source1 = "abcd";
    string target1 = "acbe";
    vector<char> original1 = {'a', 'b', 'c', 'c', 'e', 'd'};
    vector<char> changed1 = {'b', 'c', 'b', 'e', 'b', 'e'};
    vector<int> cost1 = {2, 5, 5, 1, 2, 20};
    cout << "Minimum Cost: " << solution.minimumCost(source1, target1, original1, changed1, cost1) << endl; // Output: 28

    // Test case 2
    string source2 = "aaaa";
    string target2 = "bbbb";
    vector<char> original2 = {'a', 'c'};
    vector<char> changed2 = {'c', 'b'};
    vector<int> cost2 = {1, 2};
    cout << "Minimum Cost: " << solution.minimumCost(source2, target2, original2, changed2, cost2) << endl; // Output: 12

    // Test case 3
    string source3 = "abcd";
    string target3 = "abce";
    vector<char> original3 = {'a'};
    vector<char> changed3 = {'e'};
    vector<int> cost3 = {10000};
    cout << "Minimum Cost: " << solution.minimumCost(source3, target3, original3, changed3, cost3) << endl; // Output: -1

    return 0;
}
