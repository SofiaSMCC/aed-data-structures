#include <iostream>
#include <vector>
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

    int isFull() {
        if(front_index == ((rear_index + 1) % MAX_Q_SIZE)) {
            return 1;
        }
        return 0;
    }

    int isEmpty() {
        if(front_index == rear_index) {
            return 1;
        }
        return 0;
    }

    T front() {
        return list[(front_index + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e) {
        if(isFull()) return;
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        list[rear_index] = e;
    }

    T dequeue() {
        if(isEmpty()) return list[front_index]; // Return front element if queue is empty
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        // Extract start and target positions
        int startX = start[0], startY = start[1];
        int targetX = target[0], targetY = target[1];
        
        // Create a queue
        Queue<pair<int, int>> pq;
        
        // Create arrays to store minimum cost to reach each position
        int minCost[101][101]; // assuming maximum size of 100x100 grid
        
        // Initialize minimum costs to a large value (infinity)
        const int INF = 1e9;
        for (int i = 0; i <= 100; ++i) {
            for (int j = 0; j <= 100; ++j) {
                minCost[i][j] = INF;
            }
        }
        
        // Push start position into queue with cost 0
        pq.enqueue(make_pair(startX, startY));
        minCost[startX][startY] = 0;
        
        // Directions for moving in the grid (right, left, up, down)
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        // Process nodes in the queue
        while (!pq.isEmpty()) {
            auto current = pq.dequeue();
            int curX = current.first, curY = current.second;
            
            // Check regular movements (right, left, up, down)
            for (int d = 0; d < 4; ++d) {
                int nextX = curX + directions[d][0];
                int nextY = curY + directions[d][1];
                
                // Check bounds
                if (nextX < 0 || nextX > 100 || nextY < 0 || nextY > 100) {
                    continue;
                }
                
                // Calculate cost to move to next position
                int cost = abs(nextX - curX) + abs(nextY - curY);
                
                // Update minimum cost if this path is cheaper
                if (minCost[nextX][nextY] > minCost[curX][curY] + cost) {
                    minCost[nextX][nextY] = minCost[curX][curY] + cost;
                    pq.enqueue(make_pair(nextX, nextY));
                }
            }
            
            // Check special roads
            for (auto& road : specialRoads) {
                int x1 = road[0], y1 = road[1];
                int x2 = road[2], y2 = road[3];
                int cost = road[4];
                
                // Check if current position matches one end of the special road
                if (curX == x1 && curY == y1) {
                    // Update minimum cost to reach the other end of the road
                    if (minCost[x2][y2] > minCost[curX][curY] + cost) {
                        minCost[x2][y2] = minCost[curX][curY] + cost;
                        pq.enqueue(make_pair(x2, y2));
                    }
                }
            }
        }
        
        // Return the minimum cost to reach the target position
        return minCost[targetX][targetY] == INF ? -1 : minCost[targetX][targetY];
    }
};

int main() {
    // Example usage
    vector<int> start = {1, 1};
    vector<int> target = {4, 5};
    vector<vector<int>> specialRoads = {{1, 2, 3, 3, 2}, {3, 4, 4, 5, 1}};
    
    Solution sol;
    cout << sol.minimumCost(start, target, specialRoads) << endl; // Output: 5
    
    return 0;
}
