#include <iostream>
#include <vector>
#define MAX_Q_SIZE 100

using namespace std;

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
        return front_index == ((rear_index + 1) % MAX_Q_SIZE);
    }

    int isEmpty()
    {
        return front_index == rear_index;
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
    vector<vector<int>> adj;

public:
    Graph(int n)
    {
        adj.resize(n + 1); // Using 1-based indexing for people
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // Since dislikes are bidirectional
    }

    bool bfs(vector<int> &color, int start)
    {
        Queue<int> q;
        q.enqueue(start);
        color[start] = 0; // Start coloring with group 0

        while (!q.isEmpty())
        {
            int node = q.dequeue();
            for (int neighbor : adj[node])
            {
                if (color[neighbor] == -1)
                {                                      // Not colored
                    color[neighbor] = 1 - color[node]; // Alternate color
                    q.enqueue(neighbor);
                }
                else if (color[neighbor] == color[node])
                    return false;
            }
        }
        return true;
    }

    bool isBipartite(int n)
    {
        vector<int> color(n + 1, -1); // -1 means uncolored, 0 and 1 represent two groups

        // BFS to check bipartiteness
        for (int i = 1; i <= n; ++i)
        {
            if (color[i] == -1)
            { 
                if (!bfs(color, i))
                    return false;
            }
        }
        return true;
    }
};

class Solution
{
public:
    bool possibleBipartition(int n, vector<vector<int>> &dislikes)
    {
        Graph graph(n);
        for (auto &dislike : dislikes)
            graph.addEdge(dislike[0], dislike[1]);
        return graph.isBipartite(n);
    }
};

int main()
{
    Solution sol;

    int n1 = 4;
    vector<vector<int>> dislikes1 = {{1, 2}, {1, 3}, {2, 4}};
    cout << sol.possibleBipartition(n1, dislikes1) << endl; // Output: true

    int n2 = 3;
    vector<vector<int>> dislikes2 = {{1, 2}, {1, 3}, {2, 3}};
    cout << sol.possibleBipartition(n2, dislikes2) << endl; // Output: false

    return 0;
}
