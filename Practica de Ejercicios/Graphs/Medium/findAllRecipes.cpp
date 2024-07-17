#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<string> findAllRecipes(vector<string> &recipes, vector<vector<string>> &ingredients, vector<string> &supplies)
    {
        int n = recipes.size();
        vector<vector<int>> graph(n); // Adjacency list for recipes
        int inDegree[n];              // In-degrees for each recipe
        bool canCreate[n];            // Track which recipes can be created

        // Initialize inDegree and canCreate
        for (int i = 0; i < n; i++)
        {
            inDegree[i] = 0;
            canCreate[i] = false;
        }

        // Create the graph and calculate in-degrees
        for (int i = 0; i < n; i++)
        {
            for (const string &ingredient : ingredients[i])
            {
                for (int j = 0; j < n; j++)
                {
                    if (ingredient == recipes[j])
                    {
                        graph[j].push_back(i); // ingredient (recipe) points to the recipe needing it
                        inDegree[i]++;         // Increase in-degree for the recipe needing this ingredient
                    }
                }
            }
        }

        // Mark supplies as creatable
        for (const string &supply : supplies)
        {
            for (int i = 0; i < n; i++)
            {
                if (supply == recipes[i])
                {
                    canCreate[i] = true;
                    inDegree[i] = 0; // No ingredients needed
                }
            }
        }

        vector<string> result;
        bool createdSomething;

        // Continue until no new recipes can be created
        do
        {
            createdSomething = false;

            for (int i = 0; i < n; i++)
            {
                if (!canCreate[i] && inDegree[i] == 0)
                {
                    canCreate[i] = true;
                    result.push_back(recipes[i]);
                    createdSomething = true;

                    // Reduce in-degree for all dependent recipes
                    for (int neighbor : graph[i])
                    {
                        inDegree[neighbor]--;
                    }
                }
            }
        } while (createdSomething);

        return result;
    }
};

int main()
{
    Solution solution;

    vector<string> recipes = {"bread", "sandwich", "burger"};
    vector<vector<string>> ingredients = {{"yeast", "flour"}, {"bread", "meat"}, {"sandwich", "meat", "bread"}};
    vector<string> supplies = {"yeast", "flour", "meat"};

    vector<string> result = solution.findAllRecipes(recipes, ingredients, supplies);

    for (const string &recipe : result)
    {
        cout << recipe << endl;
    }

    return 0;
}
