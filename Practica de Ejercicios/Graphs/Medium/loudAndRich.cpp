#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
private:
    vector<vector<int>> adj;
    vector<int> quietest_person;

    int dfs(int person, const vector<vector<int>> &richer, const vector<int> &quiet)
    {
        if (quietest_person[person] != -1)
            return quietest_person[person];

        int quietest = person;
        for (int neighbor : adj[person])
        {
            int candidate = dfs(neighbor, richer, quiet);
            if (quiet[candidate] < quiet[quietest])
                quietest = candidate;
        }

        quietest_person[person] = quietest;
        return quietest;
    }

public:
    vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet)
    {
        int n = quiet.size();
        adj.resize(n);
        quietest_person.resize(n, -1);

        for (auto &edge : richer)
            adj[edge[1]].push_back(edge[0]);

        vector<int> answer;
        for (int i = 0; i < n; ++i)
            answer.push_back(dfs(i, richer, quiet));

        return answer;
    }
};
