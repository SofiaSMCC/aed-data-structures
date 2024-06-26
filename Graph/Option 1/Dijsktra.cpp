#include <iostream>
#include <vector>
#include <limits>
#include <utility> // para std::pair

#define MAX_Q_SIZE 100
#define INF std::numeric_limits<int>::max()

template <typename T>
class Queue
{
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    Queue()
    {
        front_index = 0;
        rear_index = 0;
    }

    int isFull()
    {
        return (front_index == ((rear_index + 1) % MAX_Q_SIZE));
    }

    int isEmpty()
    {
        return (front_index == rear_index);
    }

    T front()
    {
        return list[(front_index + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e)
    {
        if (isFull())
            return;
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        list[rear_index] = e;
    }

    T dequeue()
    {
        if (isEmpty())
            return T();
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

class Grafo
{
private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList; // {destino, peso}

public:
    Grafo(int vertices)
    {
        numVertices = vertices;
        adjList.resize(vertices);
    }

    void agregarArista(int origen, int destino, int peso)
    {
        adjList[origen].emplace_back(destino, peso);
        adjList[destino].emplace_back(origen, peso); // Si el grafo es no dirigido
    }

    void dijkstra(int inicio)
    {
        std::vector<int> dist(numVertices, INF);
        dist[inicio] = 0;

        Queue<std::pair<int, int>> cola;
        cola.enqueue({0, inicio}); // {distancia, vertice}

        while (!cola.isEmpty())
        {
            auto [currentDist, u] = cola.dequeue();

            for (auto &[v, peso] : adjList[u])
            {
                if (dist[u] + peso < dist[v])
                {
                    dist[v] = dist[u] + peso;
                    cola.enqueue({dist[v], v});
                }
            }
        }

        // Imprimir distancias
        for (int i = 0; i < numVertices; ++i)
        {
            std::cout << "Distancia desde " << inicio << " a " << i << " es " << dist[i] << std::endl;
        }
    }
};

int main()
{
    Grafo g(5);
    g.agregarArista(0, 1, 10);
    g.agregarArista(0, 4, 5);
    g.agregarArista(1, 2, 1);
    g.agregarArista(4, 1, 3);
    g.agregarArista(4, 2, 9);
    g.agregarArista(4, 3, 2);
    g.agregarArista(2, 3, 4);
    g.agregarArista(3, 2, 6);

    g.dijkstra(0);

    return 0;
}
