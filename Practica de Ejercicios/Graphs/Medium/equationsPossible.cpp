#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_sets(int x, int y)
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

    bool equationsPossible(vector<string> &equations)
    {
        parent.resize(26);
        rank.resize(26);

        for (int i = 0; i < 26; ++i)
        {
            parent[i] = i;
            rank[i] = 0;
        }

        for (const string &eq : equations)
        {
            if (eq[1] == '=')
            {
                int x = eq[0] - 'a';
                int y = eq[3] - 'a';
                union_sets(x, y);
            }
        }

        for (const string &eq : equations)
        {
            if (eq[1] == '!')
            {
                int x = eq[0] - 'a';
                int y = eq[3] - 'a';
                if (find(x) == find(y))
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution sol;

    // Example usage:
    vector<string> equations1 = {"a==b", "b!=a"};
    bool result1 = sol.equationsPossible(equations1);
    cout << "Output for equations1: " << (result1 ? "true" : "false") << endl;

    vector<string> equations2 = {"b==a", "a==b"};
    bool result2 = sol.equationsPossible(equations2);
    cout << "Output for equations2: " << (result2 ? "true" : "false") << endl;

    return 0;
}
