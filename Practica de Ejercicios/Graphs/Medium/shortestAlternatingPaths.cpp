#include <vector>
#include <algorithm>
#define MAX_Q_SIZE 100

using namespace std;

// Custom Queue Class
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
            return T(); // Return default if empty
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return list[front_index];
    }
};

// Element structure for the queue
struct Element
{
    int node;
    int dist;
    int color;
};

// Graph Class
class Graph
{
private:
    vector<vector<int>> redAdj, blueAdj;

public:
    Graph(int n) : redAdj(n), blueAdj(n) {}

    void addRedEdge(int u, int v)
    {
        redAdj[u].push_back(v);
    }

    void addBlueEdge(int u, int v)
    {
        blueAdj[u].push_back(v);
    }

    vector<int> bfs(int n)
    {
        vector<vector<int>> dist(n, vector<int>(2, -1));
        dist[0][0] = dist[0][1] = 0;

        Queue<Element> q;
        q.enqueue({0, 0, 0});
        q.enqueue({0, 0, 1}); 

        while (!q.isEmpty())
        {
            auto elem = q.dequeue();
            int node = elem.node, d = elem.dist, color = elem.color;

            if (color == 0)
            { 
                for (int neighbor : blueAdj[node])
                {
                    if (dist[neighbor][1] == -1)
                    {
                        dist[neighbor][1] = d + 1;
                        q.enqueue({neighbor, d + 1, 1});
                    }
                }
            }
            else
            {
                for (int neighbor : redAdj[node])
                {
                    if (dist[neighbor][0] == -1)
                    { 
                        dist[neighbor][0] = d + 1;
                        q.enqueue({neighbor, d + 1, 0});
                    }
                }
            }
        }

        vector<int> answer(n, -1);
        for (int i = 0; i < n; ++i)
        {
            if (dist[i][0] == -1 && dist[i][1] == -1)
                answer[i] = -1;
            else if (dist[i][0] == -1)
                answer[i] = dist[i][1];
            else if (dist[i][1] == -1)
                answer[i] = dist[i][0];
            else
                answer[i] = min(dist[i][0], dist[i][1]);
        }

        return answer;
    }
};

class Solution
{
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges)
    {
        Graph graph(n);

        for (const auto &edge : redEdges)
            graph.addRedEdge(edge[0], edge[1]);
        for (const auto &edge : blueEdges)
            graph.addBlueEdge(edge[0], edge[1]);
        return graph.bfs(n);
    }
};
