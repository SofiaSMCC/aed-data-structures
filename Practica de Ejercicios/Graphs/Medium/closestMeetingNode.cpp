#include <iostream>
#include <vector>
using namespace std;

#define MAX_Q_SIZE 100

// Queue class implementation
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

// Graph class implementation
class Graph
{
private:
    vector<int> edges;

public:
    Graph(vector<int> &edges) : edges(edges) {}

    int closestMeetingNode(int node1, int node2)
    {
        int n = edges.size();
        vector<int> dist1(n, -1), dist2(n, -1);

        // BFS from node1 to find distances
        bfs(node1, dist1);

        // BFS from node2 to find distances
        bfs(node2, dist2);

        // Find node with minimum max(dist1[node], dist2[node])
        int minMaxDist = INT_MAX;
        int closestNode = -1;

        for (int i = 0; i < n; ++i)
        {
            if (dist1[i] != -1 && dist2[i] != -1)
            {
                int maxDist = max(dist1[i], dist2[i]);
                if (maxDist < minMaxDist)
                {
                    minMaxDist = maxDist;
                    closestNode = i;
                }
            }
        }

        return closestNode;
    }

private:
    void bfs(int start, vector<int> &dist)
    {
        int n = edges.size();
        Queue<int> q;
        q.enqueue(start);
        dist[start] = 0;

        while (!q.isEmpty())
        {
            int node = q.dequeue();
            int nextNode = edges[node];
            if (nextNode != -1 && dist[nextNode] == -1)
            {
                dist[nextNode] = dist[node] + 1;
                q.enqueue(nextNode);
            }
        }
    }
};

// Solution class using Graph class
class Solution
{
public:
    int closestMeetingNode(vector<int> &edges, int node1, int node2)
    {
        Graph graph(edges);
        return graph.closestMeetingNode(node1, node2);
    }
};

// Main function for testing
int main()
{
    // Example 1
    vector<int> edges1 = {2, 2, 3, -1};
    int node1_1 = 0, node2_1 = 1;
    Solution sol1;
    cout << "Output for Example 1: " << sol1.closestMeetingNode(edges1, node1_1, node2_1) << endl; // Expected output: 2

    // Example 2
    vector<int> edges2 = {1, 2, -1};
    int node1_2 = 0, node2_2 = 2;
    Solution sol2;
    cout << "Output for Example 2: " << sol2.closestMeetingNode(edges2, node1_2, node2_2) << endl; // Expected output: 2

    return 0;
}
