#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution
{
public:
    vector<int> countOfPairs(int n, int x, int y)
    {
        vector<int> result(n, 0);

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                int dist = calculateDistance(i, j, x, y);

                if (dist > 0 && dist <= n)
                { // Verifica que dist esté dentro del rango válido
                    result[dist - 1]++;
                }
            }
        }

        return result;
    }

private:
    int calculateDistance(int i, int j, int x, int y)
    {
        int dist = abs(i - j);

        int option1 = abs(i - x) + abs(j - y) + 1;
        int option2 = abs(i - y) + abs(j - x) + 1;

        return min(dist, min(option1, option2));
    }
};

int main()
{
    Solution sol;

    int n1 = 3, x1 = 1, y1 = 3;
    vector<int> result1 = sol.countOfPairs(n1, x1, y1);
    cout << "Output for n = 3, x = 1, y = 3: ";
    for (int num : result1)
    {
        cout << num << " ";
    }
    cout << endl;

    int n2 = 5, x2 = 2, y2 = 4;
    vector<int> result2 = sol.countOfPairs(n2, x2, y2);
    cout << "Output for n = 5, x = 2, y = 4: ";
    for (int num : result2)
    {
        cout << num << " ";
    }
    cout << endl;

    int n3 = 4, x3 = 1, y3 = 1;
    vector<int> result3 = sol.countOfPairs(n3, x3, y3);
    cout << "Output for n = 4, x = 1, y = 1: ";
    for (int num : result3)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
