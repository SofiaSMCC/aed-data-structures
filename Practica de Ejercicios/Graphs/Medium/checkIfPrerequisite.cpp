#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int V;                       // Number of vertices (courses)
    vector<vector<int>> adjList; // Adjacency list to store prerequisites

public:
    Graph(int numCourses)
    {
        V = numCourses;
        adjList.resize(V);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    // Method to perform DFS to check if there's a path from u to v
    bool isReachable(int u, int v, vector<bool> &visited)
    {
        if (u == v)
            return true;
        visited[u] = true;
        for (int neighbor : adjList[u])
        {
            if (!visited[neighbor] && isReachable(neighbor, v, visited))
                return true;
        }
        return false;
    }

    // Method to answer queries if u is a prerequisite of v
    bool isPrerequisite(int u, int v)
    {
        vector<bool> visited(V, false);
        return isReachable(u, v, visited);
    }
};

class Solution
{
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries)
    {
        Graph graph(numCourses);

        // Build the graph with prerequisites
        for (auto &pre : prerequisites)
            graph.addEdge(pre[0], pre[1]);

        // Answer the queries using the graph
        vector<bool> answer;
        for (auto &query : queries)
        {
            int u = query[0];
            int v = query[1];
            answer.push_back(graph.isPrerequisite(u, v));
        }
        return answer;
    }
};

int main()
{
    Solution sol;

    // Example 1
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    vector<vector<int>> queries1 = {{0, 1}, {1, 0}};
    vector<bool> result1 = sol.checkIfPrerequisite(numCourses1, prerequisites1, queries1);
    cout << "Example 1 Output: ";
    for (bool ans : result1)
    {
        cout << ans << " ";
    }
    cout << endl;

    // Example 2
    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {};
    vector<vector<int>> queries2 = {{1, 0}, {0, 1}};
    vector<bool> result2 = sol.checkIfPrerequisite(numCourses2, prerequisites2, queries2);
    cout << "Example 2 Output: ";
    for (bool ans : result2)
    {
        cout << ans << " ";
    }
    cout << endl;

    // Example 3
    int numCourses3 = 3;
    vector<vector<int>> prerequisites3 = {{1, 2}, {1, 0}, {2, 0}};
    vector<vector<int>> queries3 = {{1, 0}, {1, 2}};
    vector<bool> result3 = sol.checkIfPrerequisite(numCourses3, prerequisites3, queries3);
    cout << "Example 3 Output: ";
    for (bool ans : result3)
    {
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}
