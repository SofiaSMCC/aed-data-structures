#include <iostream>
#include <vector>

class DisjointSet
{
public:
    std::vector<int> parent;

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
    bool canBeSorted(std::vector<int> &nums)
    {
        int n = nums.size();
        DisjointSet ds(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (gcd(nums[i], nums[j]) > 1)
                    ds.union_(i, j);
            }
        }
        for (int i = 0; i < n; ++i)
        {
            if (ds.find(i) != ds.find(0))
                return false;
        }
        return true;
    }

private:
    int gcd(int a, int b)
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};

int main()
{
    Solution solution;

    // Ejemplo 1
    std::vector<int> nums1 = {7, 21, 3};
    std::cout << "Ejemplo 1: " << (solution.canBeSorted(nums1) ? "true" : "false") << std::endl;

    // Ejemplo 2
    std::vector<int> nums2 = {5, 2, 6, 2};
    std::cout << "Ejemplo 2: " << (solution.canBeSorted(nums2) ? "true" : "false") << std::endl;

    return 0;
}
