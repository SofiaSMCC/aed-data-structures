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
        if (isEmpty())
            return T();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return list[front_index];
    }
};

class Graph
{
private:
    int n;
    vector<vector<int>> adj;

public:
    Graph(int nodes)
    {
        n = nodes;
        adj.resize(n);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int BFS(int start, vector<bool> &visited, vector<int> &restricted)
    {
        Queue<int> q;
        q.enqueue(start);
        visited[start] = true;

        int reachableCount = 0;
        while (!q.isEmpty())
        {
            int node = q.dequeue();
            reachableCount++;

            // Traverse neighbors
            for (int neighbor : adj[node])
            {
                if (!visited[neighbor] && !isRestricted(neighbor, restricted))
                {
                    visited[neighbor] = true;
                    q.enqueue(neighbor);
                }
            }
        }

        return reachableCount;
    }

    bool isRestricted(int node, vector<int> &restricted)
    {
        for (int r : restricted)
        {
            if (node == r)
            {
                return true;
            }
        }
        return false;
    }
};

class Solution
{
public:
    int reachableNodes(int n, vector<vector<int>> &edges, vector<int> &restricted)
    {
        Graph graph(n);

        // Build the graph
        for (auto &edge : edges)
        {
            graph.addEdge(edge[0], edge[1]);
        }

        // Perform BFS from node 0
        vector<bool> visited(n, false);
        visited[0] = true; // Node 0 is always reachable
        return graph.BFS(0, visited, restricted);
    }
};

int main()
{
    // Example 1
    int n1 = 7;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {3, 1}, {4, 0}, {0, 5}, {5, 6}};
    vector<int> restricted1 = {4, 5};
    Solution sol1;
    cout << "Output for Example 1: " << sol1.reachableNodes(n1, edges1, restricted1) << endl; // Expected output: 4

    // Example 2
    int n2 = 7;
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {0, 5}, {0, 4}, {3, 2}, {6, 5}};
    vector<int> restricted2 = {4, 2, 1};
    Solution sol2;
    cout << "Output for Example 2: " << sol2.reachableNodes(n2, edges2, restricted2) << endl; // Expected output: 3

    return 0;
}
