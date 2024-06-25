#include <iostream>
#include <vector>
#include <limits>

#define INF std::numeric_limits<int>::max()

class Grafo
{
private:
    int numVertices;
    std::vector<std::vector<int>> dist;

public:
    Grafo(int vertices)
    {
        numVertices = vertices;
        dist.resize(vertices, std::vector<int>(vertices, INF));
        for (int i = 0; i < vertices; ++i)
        {
            dist[i][i] = 0;
        }
    }

    void agregarArista(int origen, int destino, int peso)
    {
        dist[origen][destino] = peso;
        // Si el grafo es no dirigido, descomenta la siguiente línea
        // dist[destino][origen] = peso;
    }

    void floydWarshall()
    {
        for (int k = 0; k < numVertices; ++k)
        {
            for (int i = 0; i < numVertices; ++i)
            {
                for (int j = 0; j < numVertices; ++j)
                {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    void imprimirDistancias()
    {
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
            {
                if (dist[i][j] == INF)
                {
                    std::cout << "INF ";
                }
                else
                {
                    std::cout << dist[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    Grafo g(4);
    g.agregarArista(0, 1, 5);
    g.agregarArista(0, 3, 10);
    g.agregarArista(1, 2, 3);
    g.agregarArista(2, 3, 1);

    g.floydWarshall();

    std::cout << "Matriz de distancias más cortas entre cada par de vértices:\n";
    g.imprimirDistancias();

    return 0;
}
