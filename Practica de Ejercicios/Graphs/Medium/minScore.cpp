#include <iostream>
#include <vector>

#define MAX_Q_SIZE 100

using namespace std;

// Custom queue class
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

class Solution
{
public:
    int minScore(int n, vector<vector<int>> &roads)
    {
        // Create an adjacency list for the graph
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto &road : roads)
        {
            int u = road[0], v = road[1], d = road[2];
            graph[u].emplace_back(v, d);
            graph[v].emplace_back(u, d);
        }

        // BFS setup using custom queue
        vector<bool> visited(n + 1, false);
        Queue<int> q;
        q.enqueue(1);
        visited[1] = true;

        int result = INT_MAX;

        while (!q.isEmpty())
        {
            int node = q.dequeue();
            for (const auto &[neighbor, dist] : graph[node])
            {
                // Update the minimum score
                result = min(result, dist);
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.enqueue(neighbor);
                }
            }
        }

        return result;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> roads1 = {{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}};
    cout << solution.minScore(4, roads1) << endl; // Output: 5

    vector<vector<int>> roads2 = {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}};
    cout << solution.minScore(4, roads2) << endl; // Output: 2

    return 0;
}
