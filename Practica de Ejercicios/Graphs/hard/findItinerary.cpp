#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // Create a list to hold edges
        vector<pair<string, string>> edges;
        for (const auto& ticket : tickets) {
            edges.emplace_back(ticket[0], ticket[1]);
        }

        // Sort edges to ensure lexicographical order
        sort(edges.begin(), edges.end());

        vector<string> itinerary;
        dfs("JFK", edges, itinerary);
        return vector<string>(itinerary.rbegin(), itinerary.rend()); // Reverse the itinerary
    }

    void dfs(const string& airport, vector<pair<string, string>>& edges, vector<string>& itinerary) {
        for (size_t i = 0; i < edges.size(); ) {
            if (edges[i].first == airport) {
                string next = edges[i].second; // Get the destination
                edges.erase(edges.begin() + i); // Remove the edge
                dfs(next, edges, itinerary); // Continue DFS
                // Do not increment i here, as we removed the edge
            } else {
                ++i; // Move to the next edge
            }
        }
        itinerary.push_back(airport); // Add the airport to the itinerary after visiting all destinations
    }
};

int main() {
    Solution solution;
    vector<vector<string>> tickets1 = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    vector<string> result1 = solution.findItinerary(tickets1);
    for (const auto& airport : result1) {
        cout << airport << " ";
    }
    cout << endl;

    vector<vector<string>> tickets2 = {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
    vector<string> result2 = solution.findItinerary(tickets2);
    for (const auto& airport : result2) {
        cout << airport << " ";
    }
    cout << endl;

    return 0;
}
