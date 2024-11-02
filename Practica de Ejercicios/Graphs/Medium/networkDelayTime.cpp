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

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        const int inf = 1e9;                         // Use a large number to represent infinity
        vector<vector<pair<int, int>>> graph(n + 1); // adjacency list: [node -> (neighbor, weight)]

        // Build the graph
        for (auto &time : times)
        {
            int u = time[0];
            int v = time[1];
            int w = time[2];
            graph[u].push_back({v, w});
        }

        // Min-heap to store {distance, node}
        Queue<pair<int, int>> pq;
        vector<int> distances(n + 1, inf);
        distances[k] = 0; // Distance from source to itself is 0
        pq.enqueue({0, k});

        while (!pq.isEmpty())
        {
            auto current = pq.dequeue();
            int current_node = current.second;
            int current_distance = current.first;

            // If current distance is greater than already computed distance, skip
            if (current_distance > distances[current_node])
                continue;

            // Traverse neighbors
            for (auto &neighbor : graph[current_node])
            {
                int neighbor_node = neighbor.first;
                int weight = neighbor.second;
                int new_distance = current_distance + weight;

                // If found shorter path to neighbor, update and enqueue
                if (new_distance < distances[neighbor_node])
                {
                    distances[neighbor_node] = new_distance;
                    pq.enqueue({new_distance, neighbor_node});
                }
            }
        }

        // Find the maximum distance to any node
        int max_distance = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (distances[i] == inf)
                return -1; // Node i is not reachable
            max_distance = max(max_distance, distances[i]);
        }

        return max_distance;
    }
};

int main()
{
    Solution solution;

    // Example 1
    vector<vector<int>> times1 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n1 = 4, k1 = 2;
    cout << "Example 1 Output: " << solution.networkDelayTime(times1, n1, k1) << endl;

    // Example 2
    vector<vector<int>> times2 = {{1, 2, 1}};
    int n2 = 2, k2 = 1;
    cout << "Example 2 Output: " << solution.networkDelayTime(times2, n2, k2) << endl;

    // Example 3
    vector<vector<int>> times3 = {{1, 2, 1}};
    int n3 = 2, k3 = 2;
    cout << "Example 3 Output: " << solution.networkDelayTime(times3, n3, k3) << endl;

    return 0;
}
