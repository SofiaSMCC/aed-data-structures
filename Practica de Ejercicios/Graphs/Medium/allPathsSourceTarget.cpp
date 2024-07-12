#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<int>> &graph, int node, vector<int> &path, vector<vector<int>> &result)
{
    path.push_back(node);

    if (node == graph.size() - 1)
        result.push_back(path);
    else
    {
        for (int neighbor : graph[node])
            dfs(graph, neighbor, path, result);
    }
    path.pop_back();
}

class Solution
{
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        vector<vector<int>> result;
        vector<int> path;
        dfs(graph, 0, path, result);
        return result;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
    vector<vector<int>> result = sol.allPathsSourceTarget(graph);

    cout << "Possible paths from node 0 to node " << graph.size() - 1 << " are:" << endl;
    for (const auto &path : result)
    {
        for (int node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}