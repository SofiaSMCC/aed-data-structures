#include <iostream>
#include <vector>
using namespace std;

#define MAX_Q_SIZE 100
const int MOD = INT_MAX;

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

public:
    Graph(int n)
    {
        adjList.resize(n);
    }

    void addEdge(int u, int v, int time)
    {
        adjList[u].emplace_back(v, time);
        adjList[v].emplace_back(u, time);
    }

    vector<int> dijkstra(int start, int n)
    {
        vector<int> shortest_time(n, INT_MAX);
        Queue<int> q;

        shortest_time[start] = 0;
        q.enqueue(start);

        while (!q.isEmpty())
        {
            int u = q.dequeue();

            for (auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                int travel_time = neighbor.second;

                if (shortest_time[u] + travel_time < shortest_time[v])
                {
                    shortest_time[v] = shortest_time[u] + travel_time;
                    q.enqueue(v);
                }
            }
        }

        return shortest_time;
    }

    int countShortestPaths(int n, vector<int> &shortest_time)
    {
        vector<int> count(n, 0);
        count[0] = 1;

        for (int u = 0; u < n; ++u)
        {
            for (auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                int travel_time = neighbor.second;

                if (shortest_time[u] + travel_time == shortest_time[v])
                {
                    count[v] = (count[v] + count[u]) % MOD;
                }
            }
        }

        return count[n - 1];
    }
};

class Solution
{
public:
    int countPaths(int n, vector<vector<int>> &roads)
    {
        Graph g(n);

        for (auto &road : roads)
        {
            g.addEdge(road[0], road[1], road[2]);
        }

        vector<int> shortest_time = g.dijkstra(0, n);
        int result = g.countShortestPaths(n, shortest_time);

        return result;
    }
};

int main()
{
    Solution sol;

    int n1 = 7;
    vector<vector<int>> roads1 = {
        {0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}};

    int n2 = 2;
    vector<vector<int>> roads2 = {
        {1, 0, 10}};

    cout << "Example 1: " << sol.countPaths(n1, roads1) << endl; // Output: 4
    cout << "Example 2: " << sol.countPaths(n2, roads2) << endl; // Output: 1

    return 0;
}
