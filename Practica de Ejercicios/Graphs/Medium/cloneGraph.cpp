#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node() : val(0) {}
    Node(int _val) : val(_val) {}
    Node(int _val, vector<Node *> _neighbors) : val(_val), neighbors(_neighbors) {}
};

class Solution
{
private:
    struct NodeCopy
    {
        Node *original;
        Node *copy;
        NodeCopy *next;
        NodeCopy(Node *o, Node *c, NodeCopy *n) : original(o), copy(c), next(n) {}
    };

    NodeCopy *head;

    Node *findOrCreateCopy(Node *original)
    {
        NodeCopy *current = head;
        while (current != nullptr)
        {
            if (current->original == original)
            {
                return current->copy;
            }
            current = current->next;
        }

        Node *copy = new Node(original->val);
        head = new NodeCopy(original, copy, head);
        return copy;
    }

    void copyGraph(Node *original, Node *copy)
    {
        for (Node *neighbor : original->neighbors)
        {
            Node *neighborCopy = findOrCreateCopy(neighbor);
            copy->neighbors.push_back(neighborCopy);

            bool alreadyVisited = false;
            NodeCopy *current = head;
            while (current != nullptr)
            {
                if (current->original == neighbor)
                {
                    alreadyVisited = true;
                    break;
                }
                current = current->next;
            }

            if (!alreadyVisited)
            {
                copyGraph(neighbor, neighborCopy);
            }
        }
    }

public:
    Solution() : head(nullptr) {}

    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
            return nullptr;

        Node *copy = findOrCreateCopy(node);
        copyGraph(node, copy);
        return copy;
    }
};

int main()
{
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);

    n1->neighbors.push_back(n2);
    n1->neighbors.push_back(n4);
    n2->neighbors.push_back(n1);
    n2->neighbors.push_back(n3);
    n3->neighbors.push_back(n2);
    n3->neighbors.push_back(n4);
    n4->neighbors.push_back(n1);
    n4->neighbors.push_back(n3);

    Solution solution;
    Node *clonedGraph = solution.cloneGraph(n1);

    // Output the cloned graph
    cout << "Cloned Node 1 neighbors: ";
    for (Node *neighbor : clonedGraph->neighbors)
    {
        cout << neighbor->val << " ";
    }
    cout << endl;

    return 0;
}
