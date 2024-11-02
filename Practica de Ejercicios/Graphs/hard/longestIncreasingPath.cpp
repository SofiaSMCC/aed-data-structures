#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> memo(m, vector<int>(n, -1));
        int longestPath = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                longestPath = max(longestPath, dfs(matrix, memo, i, j));
            }
        }

        return longestPath;
    }

private:
    int dfs(const vector<vector<int>>& matrix, vector<vector<int>>& memo, int x, int y) {
        if (memo[x][y] != -1) return memo[x][y];

        int m = matrix.size();
        int n = matrix[0].size();
        int maxLength = 1;

        // Directions for moving in 4 possible ways: up, down, left, right
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            // Check boundaries and increasing condition
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && matrix[newX][newY] > matrix[x][y]) {
                maxLength = max(maxLength, 1 + dfs(matrix, memo, newX, newY));
            }
        }

        memo[x][y] = maxLength;
        return maxLength;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> matrix1 = {{9,9,4},{6,6,8},{2,1,1}};
    cout << "Longest Increasing Path: " << solution.longestIncreasingPath(matrix1) << endl; // Output: 4

    vector<vector<int>> matrix2 = {{3,4,5},{3,2,6},{2,2,1}};
    cout << "Longest Increasing Path: " << solution.longestIncreasingPath(matrix2) << endl; // Output: 4

    vector<vector<int>> matrix3 = {{1}};
    cout << "Longest Increasing Path: " << solution.longestIncreasingPath(matrix3) << endl; // Output: 1

    return 0;
}
