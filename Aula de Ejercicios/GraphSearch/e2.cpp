#include <iostream>
#include <vector>
#include <limits>
#include <utility>

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

        for (int i = 0; i < numVertices; ++i)
        {
            std::cout << "Distancia desde " << inicio << " a " << i << " es " << dist[i] << std::endl;
        }
    }
};

class Solution
{
public:
    int minimumEffortPath(std::vector<std::vector<int>> &heights)
    {
        int rows = heights.size();
        int columns = heights[0].size();

        // Binary search for the minimum effort
        int left = 0, right = 1e6; // Maximum possible difference in heights
        int result = right;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (canReachTarget(heights, rows, columns, mid))
            {
                result = mid;
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return result;
    }

private:
    bool canReachTarget(std::vector<std::vector<int>> &heights, int rows, int columns, int maxEffort)
    {
        std::vector<std::vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(columns, false));

        Queue<std::pair<int, int>> q;
        q.enqueue({0, 0});
        visited[0][0] = true;

        while (!q.isEmpty())
        {
            auto [r, c] = q.dequeue();

            if (r == rows - 1 && c == columns - 1)
            {
                return true;
            }

            for (auto &dir : directions)
            {
                int nr = r + dir[0];
                int nc = c + dir[1];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < columns && !visited[nr][nc])
                {
                    int diff = std::abs(heights[nr][nc] - heights[r][c]);
                    if (diff <= maxEffort)
                    {
                        visited[nr][nc] = true;
                        q.enqueue({nr, nc});
                    }
                }
            }
        }

        return false;
    }
};

/*
int main()
{
    // Ejemplo de uso para verificar el funcionamiento
    Solution sol;
    std::vector<std::vector<int>> heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    int result = sol.minimumEffortPath(heights);
    std::cout << "Minimum effort path: " << result << std::endl; // Expected output: 2

    return 0;
}
*/
