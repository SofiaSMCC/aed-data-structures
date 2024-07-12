#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adjList;
    vector<int> state;

public:
    Graph(int n) : adjList(n), state(n, 0) {}

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    bool dfs(int node)
    {
        if (state[node] != 0)
            return state[node] == 2;

        state[node] = 1; 

        for (int neighbor : adjList[node])
        {
            if (state[neighbor] == 1 || !dfs(neighbor))
                return false;
        }

        state[node] = 2; 
        return true;
    }

};

class Solution
{
public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        Graph g(graph.size());
        for (int i = 0; i < graph.size(); ++i)
        {
            for (int neighbor : graph[i])
                g.addEdge(i, neighbor);
        }

        vector<int> result;
        for (int i = 0; i < graph.size(); ++i)
        {
            if (g.dfs(i))
                result.push_back(i);
        }

        return result;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> graph1 = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    vector<int> result1 = sol.eventualSafeNodes(graph1);
    for (int node : result1)
    {
        cout << node << " ";
    }
    cout << endl;

    vector<vector<int>> graph2 = {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}};
    vector<int> result2 = sol.eventualSafeNodes(graph2);
    for (int node : result2)
    {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}