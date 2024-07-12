#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int V;                   
    vector<vector<int>> adj; // lista de adyacencia

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    const vector<int> &getNeighbors(int u) const
    {
        return adj[u];
    }
};

class Solution
{
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>> &paths)
    {
        Graph g(n); 

        for (auto &path : paths)
        {
            int u = path[0] - 1;
            int v = path[1] - 1;
            g.addEdge(u, v);
        }

        vector<int> answer(n, 0);

        for (int i = 0; i < n; ++i)
        {
            vector<bool> used(5, false); 

            for (int neighbor : g.getNeighbors(i))
            {
                if (answer[neighbor] != 0)
                    used[answer[neighbor]] = true;
            }

            for (int j = 1; j <= 4; ++j)
            {
                if (!used[j])
                {
                    answer[i] = j;
                    break;
                }
            }
        }
        return answer;
    }
};

int main()
{
    Solution sol;

    // Ejemplo 1
    int n1 = 3;
    vector<vector<int>> paths1 = {{1, 2}, {2, 3}, {3, 1}};
    vector<int> result1 = sol.gardenNoAdj(n1, paths1);
    cout << "Output for Example 1: ";
    for (int num : result1)
    {
        cout << num << " ";
    }
    cout << endl;

    // Ejemplo 2
    int n2 = 4;
    vector<vector<int>> paths2 = {{1, 2}, {3, 4}};
    vector<int> result2 = sol.gardenNoAdj(n2, paths2);
    cout << "Output for Example 2: ";
    for (int num : result2)
    {
        cout << num << " ";
    }
    cout << endl;

    // Ejemplo 3
    int n3 = 4;
    vector<vector<int>> paths3 = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3}, {2, 4}};
    vector<int> result3 = sol.gardenNoAdj(n3, paths3);
    cout << "Output for Example 3: ";
    for (int num : result3)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
