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
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

class Graph
{
private:
    int V;                   
    vector<vector<int>> adj; 

public:
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    vector<int> getNeighbors(int u)
    {
        return adj[u];
    }

    vector<int> calculateInDegree()
    {
        vector<int> inDegree(V, 0);
        for (int u = 0; u < V; ++u)
        {
            for (int v : adj[u])
                inDegree[v]++;
        }
        return inDegree;
    }
};

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        Graph graph(numCourses);

        for (auto &prereq : prerequisites)
            graph.addEdge(prereq[1], prereq[0]);

        vector<int> inDegree = graph.calculateInDegree();
        Queue<int> q;
        for (int i = 0; i < numCourses; ++i)
        {
            if (inDegree[i] == 0)
                q.enqueue(i);
        }

        int coursesTaken = 0;
        while (!q.isEmpty())
        {
            int current = q.dequeue();
            coursesTaken++;

            for (int neighbor : graph.getNeighbors(current))
            {
                if (--inDegree[neighbor] == 0)
                    q.enqueue(neighbor);
            }
        }
        return coursesTaken == numCourses;
    }
};

int main()
{
    Solution solution;

    // Ejemplos de uso
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    cout << "Example 1: " << solution.canFinish(numCourses1, prerequisites1) << endl;

    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    cout << "Example 2: " << solution.canFinish(numCourses2, prerequisites2) << endl;

    return 0;
}
