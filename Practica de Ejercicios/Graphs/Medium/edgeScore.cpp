#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int edgeScore(vector<int> &edges)
    {
        int n = edges.size();
        vector<int> edgeScores(n, 0);

        // Calculate edge scores
        for (int i = 0; i < n; ++i)
        {
            if (edges[i] < n)
            {
                edgeScores[edges[i]] += i;
            }
        }

        // Find node with maximum edge score
        int maxScore = -1;
        int maxNode = -1;
        for (int i = 0; i < n; ++i)
        {
            if (edgeScores[i] > maxScore || (edgeScores[i] == maxScore && i < maxNode))
            {
                maxScore = edgeScores[i];
                maxNode = i;
            }
        }

        return maxNode;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> edges1 = {1, 0, 0, 0, 0, 7, 7, 5};
    cout << "Output for Example 1: " << sol.edgeScore(edges1) << endl; // Expected output: 7

    // Example 2
    vector<int> edges2 = {2, 0, 0, 2};
    cout << "Output for Example 2: " << sol.edgeScore(edges2) << endl; // Expected output: 0

    return 0;
}
