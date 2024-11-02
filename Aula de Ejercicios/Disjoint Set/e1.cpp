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
        {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
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
        {
            parent[rootY] = rootX;
        }
    }
};

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        if (grid.empty() || grid[0].empty())
        {
            return 0;
        }
        int rows = grid.size();
        int cols = grid[0].size();
        int casillastot = rows * cols;
        DisjointSet ds(casillastot);
        int mar = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (grid[i][j] == '1')
                {
                    int current = i * cols + j;
                    if (i > 0 && grid[i - 1][j] == '1')
                    {
                        int k = current - cols;
                        ds.union_(current, k);
                    }
                    if (j > 0 && grid[i][j - 1] == '1')
                    {
                        int m = current - 1;
                        ds.union_(current, m);
                    }
                }
                else
                {
                    mar++;
                }
            }
        }
        int islas = 0;
        for (int i = 0; i < casillastot; ++i)
        {
            if (ds.find(i) == i)
            {
                islas++;
            }
        }
        return islas - mar;
    }
};

int main()
{
    Solution sol;

    // Ejemplo 1
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}};
    cout << "Ejemplo 1: " << sol.numIslands(grid1) << endl;

    // Ejemplo 2
    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};
    cout << "Ejemplo 2: " << sol.numIslands(grid2) << endl;

    return 0;
}
