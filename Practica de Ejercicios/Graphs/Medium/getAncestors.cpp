#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_Q_SIZE 100

template <typename T>
class Queue {
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    Queue() {
        front_index = 0;
        rear_index = 0;
    }

    bool isFull() {
        return front_index == ((rear_index + 1) % MAX_Q_SIZE);
    }

    bool isEmpty() {
        return front_index == rear_index;
    }

    T front() {
        if (!isEmpty()) {
            return list[(front_index + 1) % MAX_Q_SIZE];
        }
        throw runtime_error("Queue is empty");
    }

    void enqueue(T e) {
        if (!isFull()) {
            rear_index = (rear_index + 1) % MAX_Q_SIZE;
            list[rear_index] = e;
        }
    }

    T dequeue() {
        if (!isEmpty()) {
            T item = list[(front_index + 1) % MAX_Q_SIZE];
            front_index = (front_index + 1) % MAX_Q_SIZE;
            return item;
        }
        throw runtime_error("Queue is empty");
    }

    int getSize() const {
        if (rear_index >= front_index) {
            return rear_index - front_index;
        } else {
            return MAX_Q_SIZE - (front_index - rear_index);
        }
    }
};

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int v) {
        V = v;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const vector<int>& getAdj(int v) const {
        return adj[v];
    }

    int size() const {
        return V;
    }

    vector<int> bfs(int start, int level) const {
        vector<int> distances(V, -1);
        Queue<pair<int, int>> q;
        
        q.enqueue({start, 0});
        distances[start] = 0;

        while (!q.isEmpty()) {
            auto front = q.dequeue();
            int node = front.first;
            int dist = front.second;
            
            if (dist == level) {
                continue; // We only need to record distances up to the specified level
            }
            
            for (int neighbor : adj[node]) {
                if (distances[neighbor] == -1) {
                    distances[neighbor] = dist + 1;
                    q.enqueue({neighbor, dist + 1});
                }
            }
        }
        
        return distances;
    }
};

class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        int n = watchedVideos.size();
        
        // Build the graph
        Graph graph(n);
        for (int i = 0; i < n; ++i) {
            for (int j : friends[i]) {
                graph.addEdge(i, j);
            }
        }
        
        // Perform BFS to find all friends at the given level
        vector<int> distances = graph.bfs(id, level);
        
        // Collect watched videos of friends at the desired level
        vector<string> result;
        vector<int> frequency(256, 0); // Assuming videos are in ASCII range
        
        for (int i = 0; i < n; ++i) {
            if (distances[i] == level) {
                for (const string& video : watchedVideos[i]) {
                    frequency[video[0]]++; // Increment frequency based on first character
                }
            }
        }
        
        // Prepare result sorted by frequency and then alphabetically
        vector<pair<int, string>> freqVec;
        for (int i = 0; i < 256; ++i) {
            if (frequency[i] > 0) {
                freqVec.emplace_back(frequency[i], string(1, static_cast<char>(i)));
            }
        }
        
        // Custom sorting function
        sort(freqVec.begin(), freqVec.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
            if (a.first == b.first) {
                return a.second < b.second;
            } else {
                return a.first < b.first;
            }
        });
        
        for (const auto& pair : freqVec) {
            result.push_back(pair.second);
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    // Example usage
    vector<vector<string>> watchedVideos = {{"A","B"},{"C"},{"B","C"},{"D"}};
    vector<vector<int>> friends = {{1,2},{0,3},{0,3},{1,2}};
    int id = 0, level = 1;
    
    vector<string> result = sol.watchedVideosByFriends(watchedVideos, friends, id, level);
    
    // Output the result
    cout << "Output: ";
    for (const string& video : result) {
        cout << video << " ";
    }
    cout << endl;
    
    return 0;
}
