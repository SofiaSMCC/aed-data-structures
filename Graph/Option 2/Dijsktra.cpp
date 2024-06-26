#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#define MAX_Q_SIZE 100

using namespace std;

template <typename T>
class PriorityQueue
{
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    PriorityQueue()
    {
        front_index = 0;
        rear_index = 0;
    }

    int isFull()
    {
        return front_index == ((rear_index + 1) % MAX_Q_SIZE);
    }

    int isEmpty()
    {
        return front_index == rear_index;
    }

    void enqueue(T e)
    {
        if (isFull())
            return;
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        list[rear_index] = e;
        push_heap(list + front_index, list + rear_index + 1, greater<T>());
    }

    T dequeue()
    {
        if (isEmpty())
            return T();
        pop_heap(list + front_index, list + rear_index + 1, greater<T>());
        T item = list[rear_index];
        rear_index = (rear_index - 1 + MAX_Q_SIZE) % MAX_Q_SIZE;
        return item;
    }

    T front()
    {
        if (isEmpty())
            return T();
        return list[front_index];
    }
};

class Solution
{
public:
    vector<int> dijkstra(int V, int src, const vector<vector<int>> &edges)
    {
        // Crear una representación del grafo a partir de las aristas
        vector<vector<pair<int, int>>> graph(V);
        for (const auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            graph[u].emplace_back(v, w);
        }

        // Paso 1: Inicializar distancias desde src a todos los otros nodos como INFINITO
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Paso 2: Crear una cola de prioridad para gestionar los nodos
        PriorityQueue<pair<int, int>> pq;
        pq.enqueue({0, src});

        while (!pq.isEmpty())
        {
            int u = pq.front().second;
            pq.dequeue();

            // Paso 3: Relajar todas las aristas adyacentes
            for (const auto &edge : graph[u])
            {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.enqueue({dist[v], v});
                }
            }
        }

        return dist;
    }
};

int main()
{
    int V = 5; // Número de vértices en el grafo
    vector<vector<int>> edges = {
        {0, 1, 10},
        {0, 4, 3},
        {1, 2, 2},
        {1, 4, 4},
        {2, 3, 9},
        {3, 2, 7},
        {4, 1, 1},
        {4, 2, 8},
        {4, 3, 2}};

    int src = 0; // Nodo fuente

    Solution solution;
    vector<int> distances = solution.dijkstra(V, src, edges);

    // Imprimir todas las distancias
    cout << "Distancias desde el nodo fuente:" << endl;
    for (int i = 0; i < V; ++i)
    {
        if (distances[i] == INT_MAX)
        {
            cout << "INF ";
        }
        else
        {
            cout << distances[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
