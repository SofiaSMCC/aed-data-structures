#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution
{
public:
    void bellmanFord(int V, int src, const vector<vector<int>> &edges)
    {
        // Paso 1: Inicializar distancias desde src a todos los otros nodos como INFINITO
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Paso 2: Relajar todas las aristas |V| - 1 veces
        for (int i = 1; i <= V - 1; ++i)
        {
            for (const auto &edge : edges)
            {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                }
            }
        }

        // Paso 3: Verificar si hay ciclos negativos
        for (const auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                cout << "El grafo contiene un ciclo negativo" << endl;
                return;
            }
        }

        // Imprimir todas las distancias
        cout << "Distancias desde el nodo fuente:" << endl;
        for (int i = 0; i < V; ++i)
        {
            if (dist[i] == INT_MAX)
            {
                cout << "INF ";
            }
            else
            {
                cout << dist[i] << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    int V = 5; // Número de vértices en el grafo
    vector<vector<int>> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}};

    int src = 0; // Nodo fuente

    Solution solution;
    solution.bellmanFord(V, src, edges);

    return 0;
}
