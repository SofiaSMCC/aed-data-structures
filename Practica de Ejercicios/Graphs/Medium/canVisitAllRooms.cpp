#include <iostream>
#include <vector>
using namespace std;

#define MAX_STACK_SIZE 100

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
        if (!isFull())
        {
            (top_index)++;
            list[top_index] = element;
        }
    }

    T pop()
    {
        T element = peek();
        (top_index)--;
        return element;
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

class Solution
{
public:
    bool canVisitAllRooms(vector<vector<int>> &rooms)
    {
        int n = rooms.size();
        vector<bool> visited(n, false);
        Stack<int> s;
        s.push(0);
        visited[0] = true;
        int visitedCount = 1;

        while (!s.isEmpty())
        {
            int room = s.pop();

            for (int key : rooms[room])
            {
                if (!visited[key])
                {
                    s.push(key);
                    visited[key] = true;
                    visitedCount++;
                }
            }
        }

        return visitedCount == n;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> rooms1 = {{1}, {2}, {3}, {}};
    cout << (sol.canVisitAllRooms(rooms1) ? "true" : "false") << endl;

    vector<vector<int>> rooms2 = {{1, 3}, {3, 0, 1}, {2}, {0}};
    cout << (sol.canVisitAllRooms(rooms2) ? "true" : "false") << endl;

    return 0;
}