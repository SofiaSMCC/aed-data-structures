#include <iostream>
#include <vector>
#include <cmath>
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
    vector<vector<pair<int, int>>> adjList;
    int n;

public:
    Graph(int numNodes) : n(numNodes)
    {
        adjList.resize(numNodes);
    }

    void addEdge(int u, int v, int weight)
    {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }

    int bfsCount(int start)
    {
        vector<bool> visited(n, false);
        Queue<int> q;
        q.enqueue(start);
        visited[start] = true;
        int count = 0;

        while (!q.isEmpty())
        {
            int u = q.dequeue();
            count++;

            for (auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                if (!visited[v])
                {
                    visited[v] = true;
                    q.enqueue(v);
                }
            }
        }

        return count;
    }
};

class Solution
{
public:
    int maximumDetonation(vector<vector<int>> &bombs)
    {
        int n = bombs.size();
        Graph g(n);

        // Build graph
        for (int i = 0; i < n; ++i)
        {
            int xi = bombs[i][0];
            int yi = bombs[i][1];
            int ri = bombs[i][2];

            for (int j = i + 1; j < n; ++j)
            {
                int xj = bombs[j][0];
                int yj = bombs[j][1];
                int rj = bombs[j][2];

                int distSq = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);
                int sumR = ri + rj;

                if (distSq <= sumR * sumR)
                {
                    g.addEdge(i, j, 1);
                }
            }
        }

        // Find maximum detonations
        int maxDetonations = 0;
        for (int i = 0; i < n; ++i)
        {
            maxDetonations = max(maxDetonations, g.bfsCount(i));
        }

        return maxDetonations;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<vector<int>> bombs1 = {{2, 1, 3}, {6, 1, 4}};
    cout << "Example 1: " << sol.maximumDetonation(bombs1) << endl; // Output: 2

    // Example 2
    vector<vector<int>> bombs2 = {{1, 1, 5}, {10, 10, 5}};
    cout << "Example 2: " << sol.maximumDetonation(bombs2) << endl; // Output: 1

    // Example 3
    vector<vector<int>> bombs3 = {{1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}};
    cout << "Example 3: " << sol.maximumDetonation(bombs3) << endl; // Output: 5

    return 0;
}
