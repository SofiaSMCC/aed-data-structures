#include <iostream>
#include <vector>

#define MAX_STACK_SIZE 10

template <typename T>
class Stack
{
    T list[MAX_STACK_SIZE];
    int top_index;

public:
    Stack() : top_index(-1) {}

    bool isFull()
    {
        if (top_index >= MAX_STACK_SIZE - 1)
            return true;
        return false;
    }

    bool isEmpty()
    {
        if (top_index == -1)
            return true;
        return false;
    }

    T top()
    {
        return list[top_index];
    }

    void push(T element)
    {
        if (isFull())
            return;

        (top_index)++;
        list[top_index] = element;
    }

    T pop()
    {
        T element = peek();
        (top_index)--;
        return element;
    }

    void print()
    {
        if (isEmpty())
            return;

        for (int i = top_index; i >= 0; --i)
        {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    }

    void clear()
    {
        top_index = -1;
    }

    int getSize()
    {
        return top_index + 1;
    }

    bool search(T element)
    {
        for (int i = 0; i <= top_index; ++i)
        {
            if (list[i] == element)
                return true;
        }
        return false;
    }
};

#define MAX_Q_SIZE 100

template <typename T>
class Queue {
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    Queue() {
        front_index = 0;
        rear_index = 0;
    }

    int isFull() {
        if(front_index == ((rear_index + 1) % MAX_Q_SIZE)) {
            return 1;
        }
        return 0;
    }

    int isEmpty() {
        if(front_index == rear_index) {
            return 1;
        }
        return 0;
    }

    T front() {
        return list[(front_index + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e) {
        if(isFull()) return;
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        list[rear_index] = e;
    }

    T dequeue() {
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

class SimplifiedGraph {
private:
    struct Node {
        std::vector<std::pair<int, int>> adj; // (child, weight)
    };

    std::vector<Node> nodes;

public:
    void addNode() {
        nodes.emplace_back(Node());
    }

    void addEdge(int a, int b, int weight) {
        nodes[a].adj.emplace_back(b, weight);
    }

    Node getNode(int value) {
        return nodes[value];
    }

    void BFS(int src) {
        Queue<int> q;
        std::vector<bool> visited(nodes.size(), false);

        q.enqueue(src);
        visited[src] = true;

        while (!q.isEmpty()) {
            int node = q.front();
            q.dequeue();

            std::cout << node << " ";

            for (const auto &child : nodes[node].adj) {
                if (!visited[child.first]) {
                    q.enqueue(child.first);
                    visited[child.first] = true;
                }
            }
        }
    }

    void DFS(int src) {
        Stack<int> s;
        std::vector<bool> visited(nodes.size(), false);

        s.push(src);

        while (!s.isEmpty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                std::cout << node << " ";
                visited[node] = true;

                for (auto it = nodes[node].adj.rbegin(); it != nodes[node].adj.rend(); ++it) {
                    if (!visited[it->first]) {
                        s.push(it->first);
                    }
                }
            }
        }
    }

    bool DFS(int curr, int des, std::vector<int> &vis) {
        if (curr == des) {
            return true;
        }

        vis[curr] = 1;
        for (auto x : nodes[curr].adj) {
            if (!vis[x.first]) {
                if (DFS(x.first, des, vis)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isPath(int src, int des) {
        std::vector<int> vis(nodes.size(), 0);
        return DFS(src, des, vis);
    }

    std::vector<std::vector<int>> findSCC() {
        int n = nodes.size();
        std::vector<std::vector<int>> ans;
        std::vector<int> is_scc(n, 0);

        for (int i = 0; i < n; ++i) {
            if (!is_scc[i]) {
                std::vector<int> scc;
                scc.push_back(i);

                for (int j = 0; j < n; ++j) {
                    if (i != j && !is_scc[j] && isPath(i, j) && isPath(j, i)) {
                        is_scc[j] = 1;
                        scc.push_back(j);
                    }
                }

                ans.push_back(scc);
            }
        }
        return ans;
    }

    void relax(int u, int v, int weight, std::vector<int> &dist) {
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
        }
    }

    std::vector<int> dijkstra(int src) {
        int n = nodes.size();
        std::vector<int> dist(n, INT_MAX);
        std::vector<bool> sptSet(n, false);

        dist[src] = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = -1;

            for (int i = 0; i < n; i++) {
                if (!sptSet[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }

            sptSet[u] = true;

            for (const auto &[v, weight] : nodes[u].adj) {
                relax(u, v, weight, dist);
            }
        }
        return dist;
    }

    void topologicalSortUtil(int v, std::vector<bool> &visited, Stack<int> &stack) {
        visited[v] = true;

        for (const auto &pair : nodes[v].adj) {
            int i = pair.first;
            if (!visited[i])
                topologicalSortUtil(i, visited, stack);
        }
        stack.push(v);
    }

    void topologicalSort() {
        Stack<int> stack;
        std::vector<bool> visited(nodes.size(), false);

        for (int i = 0; i < nodes.size(); i++) {
            if (!visited[i])
                topologicalSortUtil(i, visited, stack);
        }

        while (!stack.isEmpty()) {
            std::cout << stack.top() << " ";
            stack.pop();
        }
        std::cout << std::endl;
    }

    std::vector<int> bellmanFord(int src) {
        int n = nodes.size();
        std::vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        for (int i = 1; i <= n - 1; i++) {
            for (int u = 0; u < n; u++) {
                for (const auto& [v, weight] : nodes[u].adj) {
                    relax(u, v, weight, dist);
                }
            }
        }

        for (int u = 0; u < n; u++) {
            for (const auto& [v, weight] : nodes[u].adj) {
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    std::cout << "Graph contains negative weight cycle" << std::endl;
                    return std::vector<int>();
                }
            }
        }

        return dist;
    }

    std::vector<std::vector<int>> floydWarshall() {
        int n = nodes.size();
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX));

        for (int u = 0; u < n; u++) {
            dist[u][u] = 0;
            for (const auto& [v, weight] : nodes[u].adj) {
                dist[u][v] = weight;
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j] && dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        return dist;
    }

    void printFloydWarshal(const std::vector<std::vector<int>> &dist) {
        int n = dist.size();

        std::cout << "Shortest distances (vertex number):" << std::endl;
        std::cout << "   ";
        for (int i = 0; i < n; i++) {
            std::cout << i << "\t";
        }
        std::cout << std::endl;

        for (int i = 0; i < n; i++) {
            std::cout << i << ": ";
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INT_MAX) {
                    std::cout << "INF\t";
                } else {
                    std::cout << dist[i][j] << "\t";
                }
            }
            std::cout << std::endl;
        }
    }
};
