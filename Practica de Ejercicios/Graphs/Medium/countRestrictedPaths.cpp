#include <iostream>
#include <vector>
#include <limits>

class MinHeap
{
public:
    std::vector<std::pair<int, int>> heap; // Pair of (distance, node)

    void push(std::pair<int, int> element)
    {
        heap.push_back(element);
        siftUp(heap.size() - 1);
    }

    std::pair<int, int> pop()
    {
        std::pair<int, int> minElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return minElement;
    }

    bool empty()
    {
        return heap.empty();
    }

private:
    void siftUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index].first >= heap[parent].first)
                break;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void siftDown(int index)
    {
        int size = heap.size();
        while (index * 2 + 1 < size)
        {
            int child = index * 2 + 1;
            if (child + 1 < size && heap[child + 1].first < heap[child].first)
            {
                child++;
            }
            if (heap[index].first <= heap[child].first)
                break;
            std::swap(heap[index], heap[child]);
            index = child;
        }
    }
};

class Solution
{
public:
    int countRestrictedPaths(int n, std::vector<std::vector<int>> &edges)
    {
        std::vector<std::pair<int, int>> graph[n + 1];
        for (const auto &edge : edges)
        {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        std::vector<int> distance(n + 1, INT_MAX);
        distance[n] = 0;

        MinHeap pq;
        pq.push({0, n});

        while (!pq.empty())
        {
            auto [dist, node] = pq.pop();
            if (dist > distance[node])
                continue;

            for (const auto &neighbor : graph[node])
            {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;
                if (distance[node] + edgeWeight < distance[nextNode])
                {
                    distance[nextNode] = distance[node] + edgeWeight;
                    pq.push({distance[nextNode], nextNode});
                }
            }
        }

        long long count = 0;
        std::vector<long long> dp(n + 1, -1);
        count = dfs(1, n, distance, graph, dp);
        return count % INT_MAX;
    }

private:
    long long dfs(int current, int target, const std::vector<int> &distance,
                  const std::vector<std::pair<int, int>> graph[], std::vector<long long> &dp)
    {
        if (current == target)
            return 1;

        if (dp[current] != -1)
            return dp[current];

        long long paths = 0;
        for (const auto &neighbor : graph[current])
        {
            int nextNode = neighbor.first;
            if (distance[current] > distance[nextNode])
            {
                paths = (paths + dfs(nextNode, target, distance, graph, dp)) % INT_MAX;
            }
        }

        return dp[current] = paths;
    }
};

int main()
{
    Solution solution;
    int n1 = 5;
    std::vector<std::vector<int>> edges1 = {{1, 2, 3}, {1, 3, 3}, {2, 3, 1}, {1, 4, 2}, {5, 2, 2}, {3, 5, 1}, {5, 4, 10}};
    std::cout << solution.countRestrictedPaths(n1, edges1) << std::endl; // Output: 3

    int n2 = 7;
    std::vector<std::vector<int>> edges2 = {{1, 3, 1}, {4, 1, 2}, {7, 3, 4}, {2, 5, 3}, {5, 6, 1}, {6, 7, 2}, {7, 5, 3}, {2, 6, 4}};
    std::cout << solution.countRestrictedPaths(n2, edges2) << std::endl; // Output: 1

    return 0;
}
