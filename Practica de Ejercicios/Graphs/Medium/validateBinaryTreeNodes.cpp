#include <iostream>
#include <vector>
using namespace std;

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;
public:
    DisjointSet(int size)
    {
        parent.resize(size);
        rank.resize(size);
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2)
        {
            if (rank[s1] < rank[s2])
                parent[s1] = s2;
            else if (rank[s1] > rank[s2])
                parent[s2] = s1;
            else
            {
                parent[s2] = s1;
                rank[s1] += 1;
            }
            return true;
        }
        return false;
    }
};

class Solution
{
public:
    bool validateBinaryTreeNodes(int n, vector<int> &leftChild, vector<int> &rightChild)
    {
        vector<int> indegree(n, 0);
        DisjointSet ds(n);

        for (int i = 0; i < n; ++i)
        {
            if (leftChild[i] != -1)
            {
                indegree[leftChild[i]]++;
                if (indegree[leftChild[i]] > 1 || !ds.unite(i, leftChild[i]))
                    return false;
            }
            if (rightChild[i] != -1)
            {
                indegree[rightChild[i]]++;
                if (indegree[rightChild[i]] > 1 || !ds.unite(i, rightChild[i]))
                    return false;
            }
        }

        int rootCount = 0;
        for (int i = 0; i < n; ++i)
        {
            if (indegree[i] == 0)
                rootCount++;
        }
        return rootCount == 1;
    }
};

int main()
{
    Solution solution;

    vector<int> leftChild1 = {1, -1, 3, -1};
    vector<int> rightChild1 = {2, -1, -1, -1};
    cout << "Output for example 1: " << boolalpha << solution.validateBinaryTreeNodes(4, leftChild1, rightChild1) << endl; // Output: true

    vector<int> leftChild2 = {1, -1, 3, -1};
    vector<int> rightChild2 = {2, 3, -1, -1};
    cout << "Output for example 2: " << boolalpha << solution.validateBinaryTreeNodes(4, leftChild2, rightChild2) << endl; // Output: false

    vector<int> leftChild3 = {1, 0};
    vector<int> rightChild3 = {-1, -1};
    cout << "Output for example 3: " << boolalpha << solution.validateBinaryTreeNodes(2, leftChild3, rightChild3) << endl; // Output: false

    return 0;
}
