#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisjointSet
{
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        vector<pair<int, pair<int, int>>> edges;

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int cost = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                edges.push_back({cost, {i, j}});
            }
        }

        sort(edges.begin(), edges.end());

        DisjointSet ds(n);
        int minCost = 0;
        int edgesUsed = 0;

        for (auto edge : edges)
        {
            int cost = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            if (ds.find(u) != ds.find(v))
            {
                ds.unionSets(u, v);
                minCost += cost;
                edgesUsed++;

                if (edgesUsed == n - 1)
                    break;
            }
        }
        return minCost;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> points1 = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
    vector<vector<int>> points2 = {{3, 12}, {-2, 5}, {-4, 1}};

    cout << sol.minCostConnectPoints(points1) << endl; // Output: 20
    cout << sol.minCostConnectPoints(points2) << endl; // Output: 18

    return 0;
}
