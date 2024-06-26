#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    void floydWarshall(vector<vector<int>>& graph) {
        int V = graph.size();

        // Inicializar la matriz de distancias con los pesos dados
        vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
        for (int i = 0; i < V; ++i) {
            dist[i][i] = 0; // Distancia de un nodo a sí mismo es 0
            for (int j = 0; j < V; ++j) {
                if (graph[i][j] != 0) {
                    dist[i][j] = graph[i][j];
                }
            }
        }

        // Algoritmo de Floyd-Warshall
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    // Si el camino de i a j a través de k es más corto, actualizarlo
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // Imprimir la matriz de distancias mínimas
        cout << "Matriz de distancias mínimas:" << endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int V = 4; // Número de vértices en el grafo
    vector<vector<int>> graph = {
        {0, 5, INT_MAX, 10},
        {INT_MAX, 0, 3, INT_MAX},
        {INT_MAX, INT_MAX, 0, 1},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };

    Solution solution;
    solution.floydWarshall(graph);

    return 0;
}
