#include <iostream>
#include <vector>

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

class GraphMatrix
{
public:
    bool **adjMatrix;
    int size;

    GraphMatrix()
    {
        adjMatrix = nullptr;
        size = 0;
    }

    GraphMatrix(int _size)
    {
        size = _size;
        adjMatrix = new bool *[size];

        for (int i = 0; i < size; i++)
        {
            adjMatrix[i] = new bool[size];

            for (int j = 0; j < size; j++)
            {
                adjMatrix[i][j] = false;
            }
        }
    }

    ~GraphMatrix()
    {
        for (int i = 0; i < size; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }

    void addEdge(int i, int j, bool bidirectional)
    {
        adjMatrix[i][j] = true;
        if (bidirectional)
            adjMatrix[j][i] = true;
    }

    void removeEdge(int i, int j, bool bidirectional)
    {
        adjMatrix[i][j] = false;
        if (bidirectional)
            adjMatrix[j][i] = false;
    }

    bool hasEdge(int i, int j)
    {
        return adjMatrix[i][j];
    }

    std::vector<int> getNeighbors(int i)
    {
        std::vector<int> neighbors;
        for (int j = 0; j < size; j++)
        {
            if (adjMatrix[i][j])
            {
                neighbors.push_back(j);
            }
        }
        return neighbors;
    }

    int getDegree(int i)
    {
        int degree = 0;
        for (int j = 0; j < size; j++)
        {
            if (adjMatrix[i][j])
            {
                degree++;
            }
        }
        return degree;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << i << " : ";
            for (int j = 0; j < size; j++)
                std::cout << adjMatrix[i][j] << " ";
            std::cout << "\n";
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

            for (int i = 0; i < size; ++i)
            {
                if (adjMatrix[vertex][i] && !visited[i])
                {
                    visited[i] = true;
                    q.enqueue(i);
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

            for (int i = size - 1; i >= 0; --i)
            {
                if (adjMatrix[vertex][i] && !visited[i])
                {
                    stack.push(i);
                }
            }
        }
        std::cout << std::endl;
    }
};