#include <iostream>
#include <vector>
#include <algorithm>

class DisjointSet
{
private:
    std::vector<int> parent, rank;

public:
    DisjointSet(int size)
    {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v)
    {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v)
        {
            if (rank[root_u] > rank[root_v])
            {
                parent[root_v] = root_u;
            }
            else
            {
                parent[root_u] = root_v;
                if (rank[root_u] == rank[root_v])
                {
                    rank[root_v]++;
                }
            }
        }
    }
};

class GraphList
{
private:
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    int size;

public:
    GraphList(int _size) : size(_size) {}

    void addEdge(int i, int j, int weight, bool bidirectional = true)
    {
        edges.push_back({weight, {i, j}});
        if (bidirectional)
        {
            edges.push_back({weight, {j, i}});
        }
    }

    void printEdges()
    {
        for (auto edge : edges)
        {
            std::cout << edge.second.first << " - " << edge.second.second << " : " << edge.first << std::endl;
        }
    }

    void KruskalMST()
    {
        std::vector<std::pair<int, std::pair<int, int>>> result;
        std::sort(edges.begin(), edges.end());

        DisjointSet ds(size);

        for (auto edge : edges)
        {
            int u = edge.second.first;
            int v = edge.second.second;

            if (ds.find(u) != ds.find(v))
            {
                ds.unite(u, v);
                result.push_back(edge);
            }
        }

        std::cout << "Edges in MST by Kruskal's algorithm:" << std::endl;
        for (auto edge : result)
        {
            std::cout << edge.second.first << " - " << edge.second.second << " : " << edge.first << std::endl;
        }
    }
};

/*
int main()
{
    GraphList g(4);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.KruskalMST();

    return 0;
}
*/