#include <iostream>
#include <vector>
using namespace std;

void dfs(int n, vector<vector<int>> &grafo, vector<bool> &visi)
{
    visi[n] = true;
    for (int i : grafo[n])
    {
        if (!visi[i])
        {
            dfs(i, grafo, visi);
        }
    }
}

class Solution
{
public:
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        // si las conexiones son menores que los nodos totales -1, no es posible conectar todo.
        if (connections.size() < n - 1)
            return -1;
        vector<vector<int>> grafo(n);
        for (vector<int> c : connections)
        {
            grafo[c[0]].push_back(c[1]);
            grafo[c[1]].push_back(c[0]);
        }
        // visitar los nodos
        vector<bool> visi(n, false);
        int retirado = 0;
        // usar dfs para saber cual no está visitado con las conexiones dadas.
        for (int i = 0; i < n; i++)
        {
            if (!visi[i])
            {
                dfs(i, grafo, visi);
                retirado++;
            }
        }
        return retirado - 1;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> connections = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
    int n = 6;
    vector<vector<int>> connections1 = {{0, 1}, {0, 2}, {1, 2}};
    int n1 = 4;
    cout << sol.makeConnected(n1, connections1) << endl;
    cout << sol.makeConnected(n, connections) << endl;
}