#include <iostream>
#include <vector>
#define MAX_STACK_SIZE 100
using namespace std;

template <typename T>
class Stack
{
private:
    T list[MAX_STACK_SIZE];
    int top_index;

public:
    Stack() : top_index(-1) {}

    bool isFull() const
    {
        return top_index >= MAX_STACK_SIZE - 1;
    }

    bool isEmpty() const
    {
        return top_index == -1;
    }

    T top() const
    {
        return list[top_index];
    }

    void push(T e)
    {
        if (!isFull())
        {
            top_index++;
            list[top_index] = e;
        }
    }

    T pop()
    {
        if (!isEmpty())
        {
            T item = top();
            top_index--;
            return item;
        }
        return T(); 
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

        int m = grid.size();
        int n = grid[0].size();
        int contadorIslas = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1' && !visited[i][j])
                {
                    contadorIslas++;
                    Stack<pair<int, int>> s;
                    s.push({i, j});
                    visited[i][j] = true;

                    while (!s.isEmpty())
                    {
                        auto [x, y] = s.pop();

                        for (auto [dx, dy] : directions)
                        {
                            int newX = x + dx;
                            int newY = y + dy;

                            if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                                grid[newX][newY] == '1' && !visited[newX][newY])
                            {
                                s.push({newX, newY});
                                visited[newX][newY] = true;
                            }
                        }
                    }
                }
            }
        }

        return contadorIslas;
    }
};

int main()
{
    vector<vector<char>> grid = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '1', '1'}};

    Solution sol;
    int num = sol.numIslands(grid);
    cout << num << endl;

    return 0;
}
