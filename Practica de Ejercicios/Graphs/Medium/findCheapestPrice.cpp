#include <iostream>
#include <vector>
#include <limits.h>

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

class MinHeap
{
private:
    vector<vector<int>> heap;

    void heapify_up(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[parent][0] <= heap[index][0])
                break;
            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void heapify_down(int index)
    {
        int size = heap.size();
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left][0] < heap[smallest][0])
                smallest = left;
            if (right < size && heap[right][0] < heap[smallest][0])
                smallest = right;
            if (smallest == index)
                break;

            swap(heap[smallest], heap[index]);
            index = smallest;
        }
    }

public:
    bool isEmpty()
    {
        return heap.empty();
    }

    void push(vector<int> element)
    {
        heap.push_back(element);
        heapify_up(heap.size() - 1);
    }

    vector<int> pop()
    {
        vector<int> minElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
        {
            heapify_down(0);
        }
        return minElement;
    }
};

class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto &flight : flights)
        {
            graph[flight[0]].emplace_back(flight[1], flight[2]);
        }

        MinHeap heap;
        heap.push({0, src, k + 1});

        while (!heap.isEmpty())
        {
            auto current = heap.pop();
            int cost = current[0];
            int node = current[1];
            int stops = current[2];

            if (node == dst)
            {
                return cost;
            }

            if (stops > 0)
            {
                for (const auto &neighbor : graph[node])
                {
                    heap.push({cost + neighbor.second, neighbor.first, stops - 1});
                }
            }
        }

        return -1;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
    int n = 4;
    int src = 0;
    int dst = 3;
    int k = 1;
    cout << solution.findCheapestPrice(n, flights, src, dst, k) << endl;

    return 0;
}
