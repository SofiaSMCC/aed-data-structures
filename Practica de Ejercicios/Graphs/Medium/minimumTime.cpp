#include <iostream>
#include <vector>
#define MAX_Q_SIZE 100
using namespace std;

// Definición de la clase Queue con tamaño máximo
template <typename T>
class Queue {
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    Queue() {
        front_index = 0;
        rear_index = 0;
    }

    int isFull() {
        return (front_index == ((rear_index + 1) % MAX_Q_SIZE));
    }

    int isEmpty() {
        return (front_index == rear_index);
    }

    T front() {
        return list[(front_index + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e) {
        if (isFull()) return;
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        list[rear_index] = e;
    }

    T dequeue() {
        if (isEmpty()) throw runtime_error("Queue is empty");
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

// Definición de la clase Graph
class Graph {
private:
    int n; // Número de nodos
    vector<pair<int, int>>* adj; // Lista de adyacencia: vector de pares (nodo, tiempo de viaje)

public:
    // Constructor
    Graph(int n) {
        this->n = n;
        adj = new vector<pair<int, int>>[n];
    }

    // Destructor
    ~Graph() {
        delete[] adj;
    }

    // Método para agregar una arista (bidireccional)
    void addEdge(int u, int v, int time) {
        adj[u].emplace_back(v, time);
        adj[v].emplace_back(u, time);
    }

    // Método para calcular los tiempos mínimos de llegada usando BFS
    vector<int> bfsMinTime(int start, vector<int>& disappear) {
        vector<int> minTime(n, -1);
        Queue<int> q;

        q.enqueue(start);
        minTime[start] = 0;

        while (!q.isEmpty()) {
            int node = q.dequeue();
            int currentTime = minTime[node];

            for (auto& neighbor : adj[node]) {
                int nextNode = neighbor.first;
                int traversalTime = neighbor.second;

                if (currentTime + traversalTime < disappear[nextNode]) {
                    if (minTime[nextNode] == -1 || currentTime + traversalTime < minTime[nextNode]) {
                        minTime[nextNode] = currentTime + traversalTime;
                        q.enqueue(nextNode);
                    }
                }
            }
        }

        return minTime;
    }
};

// Clase Solution que utiliza la clase Graph y Queue
class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        // Crear instancia de Graph
        Graph graph(n);

        // Agregar todas las aristas al grafo
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], time = edge[2];
            graph.addEdge(u, v, time);
        }

        // Calcular los tiempos mínimos de llegada desde el nodo 0 usando BFS
        vector<int> result = graph.bfsMinTime(0, disappear);

        return result;
    }
};

int main() {
    // Ejemplo de uso
    Solution sol;
    vector<vector<int>> edges = {{0, 1, 2}, {1, 2, 1}, {0, 2, 4}};
    vector<int> disappear = {1, 1, 5};
    int n = 3;
    vector<int> answer = sol.minimumTime(n, edges, disappear);

    // Imprimir el resultado
    for (int time : answer) {
        cout << time << " ";
    }
    cout << endl;

    return 0;
}
