#include <iostream>
#include <vector>
using namespace std;

class SimplifiedGraph
{
private:
    struct Node
    {
        std::vector<int> adj; // adjacent nodes
    };

    std::vector<Node> nodes;

public:
    void addNode()
    {
        nodes.emplace_back(Node());
    }

    void addEdge(int a, int b)
    {
        nodes[a].adj.push_back(b);
        nodes[b].adj.push_back(a); // undirected graph
    }

    int findCenter()
    {
        for (int i = 0; i < nodes.size(); ++i)
        {
            if (nodes[i].adj.size() == nodes.size() - 1)
                return i + 1; // Node labels start from 1
        }
        return -1; // Should never reach here if input is a valid star graph
    }
};

class Solution
{
public:
    int findCenter(vector<vector<int>> &edges)
    {
        SimplifiedGraph graph;

        // Assume nodes are labeled from 1 to n
        int n = edges.size() + 1;
        for (int i = 0; i < n; ++i)
        {
            graph.addNode();
        }

        for (const auto &edge : edges)
        {
            graph.addEdge(edge[0] - 1, edge[1] - 1);
        }

        return graph.findCenter();
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> edges1 = {{1, 2}, {2, 3}, {4, 2}};
    cout << solution.findCenter(edges1) << endl; // Output: 2

    vector<vector<int>> edges2 = {{1, 2}, {5, 1}, {1, 3}, {1, 4}};
    cout << solution.findCenter(edges2) << endl; // Output: 1

    return 0;
}
