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
            throw out_of_range("Queue is empty");
        T item = list[(front_index + 1) % MAX_Q_SIZE];
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

class Graph
{
private:
    vector<vector<int>> adj_list;

public:
    Graph(int n)
    {
        adj_list.resize(n);
    }

    void addEdge(int u, int v)
    {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    vector<int> &neighbors(int u)
    {
        return adj_list[u];
    }

    int size()
    {
        return adj_list.size();
    }

    bool isBipartite()
    {
        int n = adj_list.size();
        vector<int> colors(n, -1); // -1: uncolored, 0 and 1: two different colors

        for (int i = 0; i < n; ++i)
        {
            if (colors[i] == -1)
            { // unvisited node
                if (!bfs(colors, i))
                    return false; // found a conflict, not bipartite
            }
        }

        return true;
    }

private:
    bool bfs(vector<int> &colors, int start)
    {
        Queue<int> q;
        q.enqueue(start);
        colors[start] = 0; // color start node with 0

        while (!q.isEmpty())
        {
            int node = q.dequeue();
            int current_color = colors[node];
            int next_color = 1 - current_color; // alternate color

            for (int neighbor : adj_list[node])
            {
                if (colors[neighbor] == -1)
                { // unvisited neighbor
                    colors[neighbor] = next_color;
                    q.enqueue(neighbor);
                }
                else if (colors[neighbor] == current_color)
                    return false; // found a conflict, not bipartite
                // If colors[neighbor] == next_color, continue without enqueueing
            }
        }

        return true;
    }
};

class Solution
{
public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        Graph g(n);

        // Construct the graph
        for (int u = 0; u < n; ++u)
        {
            for (int v : graph[u])
                g.addEdge(u, v);
        }

        return g.isBipartite();
    }
};

int main()
{
    Solution solution;

    // Example 1
    vector<vector<int>> graph1 = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
    cout << "Example 1 Output: " << (solution.isBipartite(graph1) ? "true" : "false") << endl;

    // Example 2
    vector<vector<int>> graph2 = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << "Example 2 Output: " << (solution.isBipartite(graph2) ? "true" : "false") << endl;

    // Example 3
    vector<vector<int>> graph3 = {{}};
    cout << "Example 3 Output: " << (solution.isBipartite(graph3) ? "true" : "false") << endl;

    return 0;
}