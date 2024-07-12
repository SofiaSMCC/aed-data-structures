#include <iostream>
#include <vector>
using namespace std;

#define MAX_Q_SIZE 100

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
        if (front_index == ((rear_index + 1) % MAX_Q_SIZE))
        {
            return 1;
        }
        return 0;
    }

    int isEmpty()
    {
        if (front_index == rear_index)
        {
            return 1;
        }
        return 0;
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
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

class Graph
{
private:
    int n;
    vector<vector<int>> adj; // adjacency list

public:
    Graph(int n)
    {
        this->n = n;
        adj.resize(n);
    }

    void addEdge(int from, int to)
    {
        adj[from].push_back(to);
    }

    vector<int> findSources()
    {
        vector<int> indegree(n, 0);

        // Calculate indegree for each vertex
        for (int i = 0; i < n; ++i)
        {
            for (int neighbor : adj[i])
            {
                indegree[neighbor]++;
            }
        }

        vector<int> sources;

        // Collect vertices with zero indegree (sources)
        for (int i = 0; i < n; ++i)
        {
            if (indegree[i] == 0)
            {
                sources.push_back(i);
            }
        }

        return sources;
    }
};

class Solution
{
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges)
    {
        Graph g(n);

        // Build the graph
        for (auto &edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            g.addEdge(from, to);
        }

        return g.findSources();
    }
};