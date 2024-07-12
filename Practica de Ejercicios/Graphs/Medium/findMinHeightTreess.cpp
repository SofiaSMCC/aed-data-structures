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

    bool isFull()
    {
        return (rear_index + 1) % MAX_Q_SIZE == front_index;
    }

    bool isEmpty()
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
            throw out_of_range("Queue is empty");
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return list[front_index];
    }
};

class Solution
{
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        if (n == 1)
            return {0};

        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);

        for (const auto &edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }

        Queue<int> leaves;

        for (int i = 0; i < n; ++i)
        {
            if (degree[i] == 1)
                leaves.enqueue(i);
        }

        vector<int> result;

        while (n > 2)
        {
            int num_leaves = countLeaves(leaves, degree);
            n -= num_leaves;

            for (int i = 0; i < num_leaves; ++i)
            {
                int leaf = leaves.dequeue();
                for (int neighbor : adj[leaf])
                {
                    if (--degree[neighbor] == 1)
                        leaves.enqueue(neighbor);
                }
            }
        }

        while (!leaves.isEmpty())
            result.push_back(leaves.dequeue());
        return result;
    }

private:
    int countLeaves(Queue<int> &queue, vector<int> &degree)
    {
        int count = 0;
        Queue<int> temp;

        while (!queue.isEmpty())
        {
            int node = queue.dequeue();
            temp.enqueue(node);
            count++;
        }

        while (!temp.isEmpty())
        {
            int node = temp.dequeue();
            queue.enqueue(node);
        }
        return count;
    }
};

int main()
{
    // Example usage
    int n1 = 4;
    vector<vector<int>> edges1 = {{1, 0}, {1, 2}, {1, 3}};
    Solution sol1;
    vector<int> mht1 = sol1.findMinHeightTrees(n1, edges1);
    cout << "Minimum Height Trees for n = " << n1 << ": ";
    for (int node : mht1)
    {
        cout << node << " ";
    }
    cout << endl;

    int n2 = 6;
    vector<vector<int>> edges2 = {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}};
    Solution sol2;
    vector<int> mht2 = sol2.findMinHeightTrees(n2, edges2);
    cout << "Minimum Height Trees for n = " << n2 << ": ";
    for (int node : mht2)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
