#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    int src, dest;
    double probability;
};

double bellmanFord(int n, vector<Edge> &edges, int start_node, int end_node)
{
    vector<double> maxProb(n, 0.0);
    maxProb[start_node] = 1.0;

    for (int i = 0; i < n - 1; ++i)
    {
        bool updated = false;
        for (const auto &edge : edges)
        {
            int u = edge.src;
            int v = edge.dest;
            double prob = edge.probability;

            if (maxProb[u] > 0.0 && maxProb[u] * prob > maxProb[v])
            {
                maxProb[v] = maxProb[u] * prob;
                updated = true;
            }
            if (maxProb[v] > 0.0 && maxProb[v] * prob > maxProb[u])
            {
                maxProb[u] = maxProb[v] * prob;
                updated = true;
            }
        }
        if (!updated)
            break;
    }

    return maxProb[end_node];
}

class Solution
{
public:
    double maxProbability(int n, vector<vector<int>> &edges_input, vector<double> &succProb, int start_node, int end_node)
    {
        vector<Edge> edges;
        for (int i = 0; i < edges_input.size(); ++i)
        {
            Edge edge;
            edge.src = edges_input[i][0];
            edge.dest = edges_input[i][1];
            edge.probability = succProb[i];
            edges.push_back(edge);
        }

        return bellmanFord(n, edges, start_node, end_node);
    }
};
