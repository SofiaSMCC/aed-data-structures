#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adjList;
    vector<bool> visited;

public:
    Graph(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        adjList.resize(n);
        visited.resize(n, false);

        // Construir la lista de adyacencia a partir de la matriz isConnected
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (isConnected[i][j] == 1)
                    adjList[i].push_back(j);
            }
        }
    }

    void dfs(int city)
    {
        visited[city] = true;
        for (int neighbor : adjList[city])
        {
            if (!visited[neighbor])
                dfs(neighbor);
        }
    }

    int countProvinces()
    {
        int n = adjList.size();
        int provinces = 0;

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                // Realizar DFS desde el nodo i no visitado
                dfs(i);
                provinces++;
            }
        }
        return provinces;
    }
};

class Solution
{
public:
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        Graph graph(isConnected);
        return graph.countProvinces();
    }
};