#include <iostream>
#include <vector>
#include <list>

#define MAX_Q_SIZE 100
#define MAX_STACK_SIZE 10

template <typename T>
class queue
{
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    queue() : front_index(0), rear_index(0) {}

    bool isFull()
    {
        return front_index == ((rear_index + 1) % MAX_Q_SIZE);
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
            return T();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return list[front_index];
    }
};

template <typename T>
class Stack
{
private:
    T list[MAX_STACK_SIZE];
    int top_index;

public:
    Stack() : top_index(-1) {}

    bool isFull()
    {
        return top_index >= MAX_STACK_SIZE - 1;
    }

    bool isEmpty()
    {
        return top_index == -1;
    }

    T peek()
    {
        if (isEmpty())
            return T();
        return list[top_index];
    }

    void push(T element)
    {
        if (isFull())
            return;
        list[++top_index] = element;
    }

    T pop()
    {
        if (isEmpty())
            return T();
        return list[top_index--];
    }
};

class GraphList
{
private:
    std::vector<std::list<int>> adjList;
    int size;

public:
    GraphList(int _size) : size(_size)
    {
        adjList.resize(size);
    }

    void addEdge(int i, int j, bool bidirectional = true)
    {
        adjList[i].push_back(j);
        if (bidirectional)
        {
            adjList[j].push_back(i);
        }
    }

    void removeEdge(int i, int j, bool bidirectional = true)
    {
        adjList[i].remove(j);
        if (bidirectional)
        {
            adjList[j].remove(i);
        }
    }

    bool hasEdge(int i, int j)
    {
        for (int neighbor : adjList[i])
        {
            if (neighbor == j)
                return true;
        }
        return false;
    }

    std::list<int> getNeighbors(int i)
    {
        return adjList[i];
    }

    void print()
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << i << ": ";
            for (int neighbor : adjList[i])
            {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    void BFS(int startVertex)
    {
        std::vector<bool> visited(size, false);
        queue<int> q;

        visited[startVertex] = true;
        q.enqueue(startVertex);

        while (!q.isEmpty())
        {
            int vertex = q.dequeue();
            std::cout << vertex << " ";

            for (int neighbor : adjList[vertex])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.enqueue(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }

    void DFS(int startVertex)
    {
        std::vector<bool> visited(size, false);
        Stack<int> stack;

        stack.push(startVertex);

        while (!stack.isEmpty())
        {
            int vertex = stack.pop();

            if (!visited[vertex])
            {
                std::cout << vertex << " ";
                visited[vertex] = true;
            }

            for (auto it = adjList[vertex].rbegin(); it != adjList[vertex].rend(); ++it)
            {
                if (!visited[*it])
                {
                    stack.push(*it);
                }
            }
        }
        std::cout << std::endl;
    }
};