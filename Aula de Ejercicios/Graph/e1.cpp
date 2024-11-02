#include <iostream>
#include <vector>
#include <climits>

#define MAX_Q_SIZE 100

using namespace std;

template <typename T>
class Queue
{
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

    void swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

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

        int i = rear_index;
        while (i != front_index)
        {
            int parent = (i - 1 + MAX_Q_SIZE) % MAX_Q_SIZE;
            if (list[i].first < list[parent].first)
            {
                swap(list[i], list[parent]);
                i = parent;
            }
            else
                break;
        }
    }

    T dequeue()
    {
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;

        int i = (front_index + 1) % MAX_Q_SIZE;
        int child = (2 * i) % MAX_Q_SIZE;
        while (child <= rear_index)
        {
            if (child + 1 <= rear_index && list[child + 1].first < list[child].first)
                child = (child + 1) % MAX_Q_SIZE;
            if (list[rear_index].first <= list[child].first)
                break;

            swap(list[i], list[child]);
            i = child;
            child = (2 * i) % MAX_Q_SIZE;
        }

        return item;
    }
};

class Graph
{
public:
    vector<vector<int>> heights;
    int rows, cols;

    Graph(const vector<vector<int>> &heights) : heights(heights)
    {
        rows = heights.size();
        cols = heights[0].size();
    }

    int dijkstra()
    {
        vector<vector<int>> efforts(rows, vector<int>(cols, INT_MAX));
        Queue<pair<int, pair<int, int>>> pq; // Min-heap implemented as Queue

        efforts[0][0] = 0;
        pq.enqueue({0, {0, 0}});

        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        while (!pq.isEmpty())
        {
            auto current = pq.dequeue();
            int currentEffort = current.first;
            int x = current.second.first;
            int y = current.second.second;

            if (x == rows - 1 && y == cols - 1)
            {
                return currentEffort;
            }

            for (const auto &dir : directions)
            {
                int nx = x + dir[0];
                int ny = y + dir[1];

                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
                {
                    int newEffort = max(currentEffort, abs(heights[nx][ny] - heights[x][y]));

                    if (newEffort < efforts[nx][ny])
                    {
                        efforts[nx][ny] = newEffort;
                        pq.enqueue({newEffort, {nx, ny}});
                    }
                }
            }
        }

        return 0; // Should never reach here
    }
};

class Solution
{
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        Graph graph(heights);
        return graph.dijkstra();
    }
};