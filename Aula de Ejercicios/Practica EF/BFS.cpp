#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_Q_SIZE 100

using namespace std;

template <typename T>
class Queue
{
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    Queue() : front_index(0), rear_index(0) {}

    bool isFull()
    {
        return front_index == ((rear_index + 1) % MAX_Q_SIZE);
    }

    bool isEmpty()
    {
        return front_index == rear_index;
    }

    T front()
    {
        return list[(front_index + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e)
    {
        if (!isFull())
        {
            rear_index = (rear_index + 1) % MAX_Q_SIZE;
            list[rear_index] = e;
        }
    }

    T dequeue()
    {
        if (!isEmpty())
        {
            front_index = (front_index + 1) % MAX_Q_SIZE;
            return list[front_index];
        }
        return T(); // Return default value if empty
    }
};

class Solution
{
public:
    int shortestCycleLength(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj(n);
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int minCycleLength = n + 1;

        // Buscar el ciclo más corto desde cada nodo utilizando BFS
        for (int start = 0; start < n; ++start)
        {
            int cycleLength = bfs(start, adj, n);
            if (cycleLength != -1)
                minCycleLength = min(minCycleLength, cycleLength);
        }

        return (minCycleLength == n + 1) ? -1 : minCycleLength;
    }

private:
    int bfs(int start, vector<vector<int>> &adj, int n)
    {
        vector<int> distance(n, -1);
        vector<int> parent(n, -1);
        Queue<int> q;
        q.enqueue(start);
        distance[start] = 0;

        while (!q.isEmpty())
        {
            int node = q.dequeue();

            for (int neighbor : adj[node])
            {
                if (distance[neighbor] == -1)
                {
                    distance[neighbor] = distance[node] + 1;
                    parent[neighbor] = node;
                    q.enqueue(neighbor);
                }
                else if (parent[node] != neighbor)
                    // Encontrado un ciclo
                    return distance[node] + distance[neighbor] + 1;
            }
        }
        return -1; // No se encontró ningún ciclo desde este nodo
    }
};

int main()
{
    // Ejemplo de entrada
    int n = 7;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 6}, {6, 3}};

    // Crear una instancia de la solución
    Solution sol;

    // Calcular la longitud del ciclo más corto
    int shortestCycle = sol.shortestCycleLength(n, edges);

    // Imprimir el resultado
    cout << "Shortest cycle length: " << shortestCycle << endl;

    return 0;
}
