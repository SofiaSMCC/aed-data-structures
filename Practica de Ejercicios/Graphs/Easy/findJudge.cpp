#include <iostream>
#include <vector>
using namespace std;

class SimplifiedGraph
{
private:
    struct Node
    {
        std::vector<std::pair<int, int>> adj;
    };

    std::vector<Node> nodes;

public:
    void addNode()
    {
        nodes.emplace_back(Node());
    }

    void addEdge(int a, int b, int weight = 1)
    {
        nodes[a].adj.emplace_back(b, weight);
    }

    Node getNode(int value)
    {
        return nodes[value];
    }

    bool isPath(int src, int des)
    {
        std::vector<int> vis(nodes.size(), 0);
        return DFS(src, des, vis);
    }

    bool DFS(int curr, int des, std::vector<int> &vis)
    {
        if (curr == des)
            return true;

        vis[curr] = 1;
        for (auto x : nodes[curr].adj)
        {
            if (!vis[x.first])
            {
                if (DFS(x.first, des, vis))
                    return true;
            }
        }
        return false;
    }
};

class Solution
{
public:
    int findJudge(int n, vector<vector<int>> &trust)
    {
        SimplifiedGraph graph;
        for (int i = 0; i <= n; ++i)
            graph.addNode();

        for (const auto &t : trust)
            graph.addEdge(t[0], t[1]);

        for (int i = 1; i <= n; ++i)
        {
            bool judge = true;
            for (int j = 1; j <= n; ++j)
            {
                if (i != j)
                {
                    if (!graph.isPath(j, i) || graph.isPath(i, j))
                    {
                        judge = false;
                        break;
                    }
                }
            }
            if (judge)
                return i;
        }
        return -1;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> trust1 = {{1, 2}};
    cout << solution.findJudge(2, trust1) << endl; // Output: 2

    vector<vector<int>> trust2 = {{1, 3}, {2, 3}};
    cout << solution.findJudge(3, trust2) << endl; // Output: 3

    vector<vector<int>> trust3 = {{1, 3}, {2, 3}, {3, 1}};
    cout << solution.findJudge(3, trust3) << endl; // Output: -1

    return 0;
}