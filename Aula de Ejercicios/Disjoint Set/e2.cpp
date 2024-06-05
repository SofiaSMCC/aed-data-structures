#include <iostream>
#include <vector>
using namespace std;

class DisjointSet
{
public:
    vector<int> parent;

    DisjointSet(int size)
    {
        parent.resize(size);
        for (int i = 0; i < size; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        else
        {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void union_(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
            parent[rootY] = rootX;
    }
};

class Solution
{
public:
    bool possibleBipartition(int n, vector<vector<int>> &dislikes)
    {
        DisjointSet ds(n + 1);
        for (auto &dislike : dislikes)
        {
            int person1 = dislike[0];
            int person2 = dislike[1];
            if (ds.find(person1) == ds.find(person2))
                return false;
            ds.union_(person1, person2);

        }
        return true;
    }
};

int main()
{
    Solution solution;

    // Ejemplo 1
    int n1 = 4;
    vector<vector<int>> dislikes1 = {{1, 2}, {1, 3}, {2, 4}};
    cout << "Ejemplo 1: " << (solution.possibleBipartition(n1, dislikes1) ? "true" : "false") << endl;

    // Ejemplo 2
    int n2 = 3;
    vector<vector<int>> dislikes2 = {{1, 2}, {1, 3}, {2, 3}};
    cout << "Ejemplo 2: " << (solution.possibleBipartition(n2, dislikes2) ? "true" : "false") << endl;

    return 0;
}
