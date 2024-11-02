#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_STACK_SIZE 1000

template <typename T>
class Stack
{
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
        return list[top_index];
    }

    void push(T element)
    {
        if (isFull())
        {
            std::cerr << "Stack overflow!" << std::endl;
            return;
        }
        list[++top_index] = element;
    }

    T pop()
    {
        if (isEmpty())
        {
            std::cerr << "Stack underflow!" << std::endl;
            return T(); // Return default value of T
        }
        return list[top_index--];
    }
};

class Graph
{
public:
    std::vector<std::vector<int>> adjList;
    int n;

    Graph(int vertices) : n(vertices)
    {
        adjList.resize(n);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void DFS(int start, std::vector<bool> &visited, std::vector<int> &component)
    {
        Stack<int> stack;
        stack.push(start);
        visited[start] = true;

        while (!stack.isEmpty())
        {
            int v = stack.pop();
            component.push_back(v);

            for (int neighbor : adjList[v])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    stack.push(neighbor);
                }
            }
        }
    }
};

class Solution
{
public:
    int countCompleteComponents(int n, std::vector<std::vector<int>> &edges)
    {
        Graph graph(n);
        for (const auto &edge : edges)
        {
            graph.addEdge(edge[0], edge[1]);
        }

        std::vector<bool> visited(n, false);
        int completeComponents = 0;

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                std::vector<int> component;
                graph.DFS(i, visited, component);
                if (isComplete(graph, component))
                {
                    completeComponents++;
                }
            }
        }

        return completeComponents;
    }

private:
    bool isComplete(const Graph &graph, const std::vector<int> &component)
    {
        int size = component.size();
        for (int i = 0; i < size; ++i)
        {
            for (int j = i + 1; j < size; ++j)
            {
                if (std::find(graph.adjList[component[i]].begin(), graph.adjList[component[i]].end(), component[j]) == graph.adjList[component[i]].end())
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> edges1 = {{0, 1}, {0, 2}, {1, 2}, {3, 4}};
    std::cout << "Number of complete components: " << solution.countCompleteComponents(6, edges1) << std::endl; // Output: 3

    std::vector<std::vector<int>> edges2 = {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}};
    std::cout << "Number of complete components: " << solution.countCompleteComponents(6, edges2) << std::endl; // Output: 1

    return 0;
}
