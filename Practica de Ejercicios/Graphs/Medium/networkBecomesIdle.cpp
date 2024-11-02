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
    vector<vector<int>> adjList;
    int n;

public:
    Graph(int numNodes) : n(numNodes)
    {
        adjList.resize(numNodes);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> bfsShortestPaths(int start)
    {
        vector<int> dist(n, INT_MAX);
        Queue<int> q;
        q.enqueue(start);
        dist[start] = 0;

        while (!q.isEmpty())
        {
            int u = q.dequeue();

            for (int v : adjList[u])
            {
                if (dist[v] == INT_MAX)
                {
                    dist[v] = dist[u] + 1;
                    q.enqueue(v);
                }
            }
        }

        return dist;
    }
};

class Solution
{
public:
    int networkBecomesIdle(vector<vector<int>> &edges, vector<int> &patience)
    {
        int n = patience.size();
        Graph g(n);

        // Build the graph (undirected)
        for (auto &edge : edges)
        {
            g.addEdge(edge[0], edge[1]);
        }

        // Step 1: BFS from server 0 to find shortest paths to all other servers
        vector<int> dist = g.bfsShortestPaths(0);

        // Step 2: Simulate message sending and receiving
        vector<int> sendTime(n);    // Time when each server sends its message
        vector<int> processTime(n); // Time when each server receives the reply
        int lastMessageTime = 0;

        for (int i = 1; i < n; ++i)
        {
            sendTime[i] = dist[i];        // Initial send time based on shortest path distance
            processTime[i] = 2 * dist[i]; // Initial process time (reply back time)
            lastMessageTime = max(lastMessageTime, processTime[i]);
        }

        // Step 3: Determine when the network becomes idle
        for (int i = 1; i < n; ++i)
        {
            if (patience[i] > 0)
            {
                int resendInterval = patience[i];
                while (processTime[i] < lastMessageTime)
                {
                    sendTime[i] += resendInterval;
                    processTime[i] = sendTime[i] + 2 * dist[i];
                    lastMessageTime = max(lastMessageTime, processTime[i]);
                }
            }
        }

        // Find the earliest second the network becomes idle
        int idleTime = lastMessageTime + 1;

        return idleTime;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}};
    vector<int> patience1 = {0, 2, 1};
    cout << "Example 1: " << sol.networkBecomesIdle(edges1, patience1) << endl; // Output: 8

    // Example 2
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {1, 2}};
    vector<int> patience2 = {0, 10, 10};
    cout << "Example 2: " << sol.networkBecomesIdle(edges2, patience2) << endl; // Output: 3

    return 0;
}
