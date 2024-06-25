#include <iostream>
#include <vector>
#include <limits>

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
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }
};

#define MAX_STACK_SIZE 10

template <typename T>
class Stack
{
    T list[MAX_STACK_SIZE];
    int top_index;

public:
    Stack() : top_index(-1) {}

    bool isFull()
    {
        if (top_index >= MAX_STACK_SIZE - 1)
            return true;
        return false;
    }

    bool isEmpty()
    {
        if (top_index == -1)
            return true;
        return false;
    }

    T peek()
    {
        return list[top_index];
    }

    void push(T element)
    {
        if (isFull())
            return;

        (top_index)++;
        list[top_index] = element;
    }

    T pop()
    {
        T element = peek();
        (top_index)--;
        return element;
    }

    void print()
    {
        if (isEmpty())
            return;

        for (int i = top_index; i >= 0; --i)
        {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    }

    void clear()
    {
        top_index = -1;
    }

    int getSize()
    {
        return top_index + 1;
    }

    bool search(T element)
    {
        for (int i = 0; i <= top_index; ++i)
        {
            if (list[i] == element)
                return true;
        }
        return false;
    }
};

template <typename T>
struct MinHeap {
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node() {
            left = nullptr;
            right = nullptr;
        }
    };

    Node *root;

    MinHeap() {
        root = NULL;
    };

    Node *insert(T value) {
        Node *node = new Node;
        node->data = value;

        if (root == nullptr) {
            root = node;
        } else {
            Queue<Node*> q;
            q.enqueue(root);

            while (!q.isEmpty()) {
                Node *temp = q.front();
                q.dequeue();

                if (temp->left == nullptr) {
                    temp->left = node;
                    heapifyUp(node);
                    break;
                } else if (temp->right == nullptr) {
                    temp->right = node;
                    heapifyUp(node);
                    break;
                } else {
                    q.enqueue(temp->left);
                    q.enqueue(temp->right);
                }
            }
        }

        return root;
    }

    Node *pop() {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else {
            Queue<Node*> q;
            q.enqueue(root);

            Node *node = nullptr;
            while (!q.isEmpty()) {
                node = q.front();
                q.dequeue();

                if (node->left != nullptr) {
                    q.enqueue(node->left);
                }
                if (node->right != nullptr) {
                    q.enqueue(node->right);
                }
            }

            Node *parentOfLastNode = getParent(root, node);
            std::swap(root->data, node->data);
            if (parentOfLastNode->left == node) {
                delete parentOfLastNode->left;
                parentOfLastNode->left = nullptr;
            } else {
                delete parentOfLastNode->right;
                parentOfLastNode->right = nullptr;
            }

            heapifyDown(root);
        }

        return root;
    }

    void heapifyUp(Node *node) {
        if(node == nullptr || node == root) {
            return;
        }

        Node *parent = nullptr;
        while (node != root) {
            parent = getParent(root, node);

            if(parent->data > node->data) {
                std::swap(parent->data, node->data);
            } else {
                break;
            }

            node = parent;
        }
    }

    void heapifyDown(Node *node) {
        if (node == nullptr) {
            return;
        }

        Node *maxNode = node;
        if (node->left != nullptr && node->left->data < maxNode->data) {
            maxNode = node->left;
        }
        if (node->right != nullptr && node->right->data < maxNode->data) {
            maxNode = node->right;
        }

        if (maxNode != node) {
            std::swap(node->data, maxNode->data);
            heapifyDown(maxNode);
        }
    }

    Node *getMinValue(Node *node) {
        Node *current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node *getParent(Node *root, Node *node) {
        if (root == nullptr || root == node) {
            return nullptr;
        }

        Queue<Node*> q;
        q.enqueue(root);

        while (!q.isEmpty()) {
            Node *temp = q.front();
            q.dequeue();

            if (temp->left == node || temp->right == node) {
                return temp;
            }

            if (temp->left != nullptr) {
                q.enqueue(temp->left);
            }
            if (temp->right != nullptr) {
                q.enqueue(temp->right);
            }
        }

        return nullptr;
    }

    void breadthFirstSearch() {
        Queue<Node*> q;
        q.enqueue(this->root);

        while(!q.isEmpty()) {
            Node *node = q.dequeue();
            std::cout << node->data << "\n";

            if(node->left != nullptr) {
                q.enqueue(node->left);
            }
            if(node->right != nullptr) {
                q.enqueue(node->right);
            }
        }
    }

    void inOrder(Node *node) {
        if(node == nullptr) {
            return;
        }

        inOrder(node->left);
        std::cout << node->data << "\n";
        inOrder(node->right);
    };
};


const int INF = std::numeric_limits<int>::max();

template <typename T>
struct Node {
    T data;
    bool visited;
//    int index;
    std::vector<Node*> adjNodes;
    //std::vector<std::pair<Node<T>*, int>> adjNodes;

    Node() {
        visited = false;
    }
};

template <typename T>
class GraphList {
private:
    std::vector<Node<T>*> nodes;
//    int indexCounter;

public:
    GraphList() {
//        indexCounter = 0;
    }

    ~GraphList() {
        for (Node<T>* node : nodes) {
            delete node;
        }
    }

    void addNode(T value) {
        if(!getNode(value)) {
            Node<T> *newNode = new Node<T>();
            newNode->data = value;
//            newNode->index = indexCounter++;
            nodes.push_back(newNode);
        }
    }

    Node<T> *getNode(T value) {
        for (Node<T>* node : nodes) {
            if (node->data == value) {
                return node;
            }
        }
        return nullptr;
    }

    void addEdge(T node1, T node2) {
        Node<T> *fromNode = getNode(node1);
        Node<T> *toNode = getNode(node2);

        if (fromNode && toNode) {
            fromNode->adjNodes.push_back(toNode);
            //toNode->adjNodes.push_back(fromNode); // Uncomment if bidirectional
        }
    }

    void addEdge(T node1, T node2, int weight) {
        Node<T> *fromNode = getNode(node1);
        Node<T> *toNode = getNode(node2);

        if (fromNode && toNode) {
            fromNode->adjNodes.push_back({toNode, weight});
            //toNode->adjNodes.push_back(fromNode, weight); // Uncomment if bidirectional
        }
    }

    void BFS(T startValue) {
        Node<T>* startNode = getNode(startValue);
        if (!startNode) {
            return;
        }

        Queue<Node<T>*> q;
        q.enqueue(startNode);
        startNode->visited = true;

        while (!q.isEmpty()) {
            Node<T> *currentNode = q.front();
            q.dequeue();
            std::cout << currentNode->data << " ";

            for (Node<T>* adjNode : currentNode->adjNodes) {
                if (!adjNode->visited) {
                    q.enqueue(adjNode);
                    adjNode->visited = true;
                }
            }
        }

        for (Node<T>* node : nodes) {
            node->visited = false;
        }
    }

    void DFS(T startValue) {
        Node<T>* startNode = getNode(startValue);
        if (!startNode) {
            return;
        }

        Stack<Node<T>*> s;
        s.push(startNode);
        startNode->visited = true;

        while (!s.isEmpty()) {
            Node<T> *currentNode = s.top();
            s.pop();
            std::cout << currentNode->data << " ";

            for (Node<T> *adjNode : currentNode->adjNodes) {
                if (!adjNode->visited) {
                    s.push(adjNode);
                    adjNode->visited = true;
                }
            }
        }

        for (Node<T>* node : nodes) {
            node->visited = false;
        }
    }

    bool DFS(T startValue, T endValue) {
        Node<T>* startNode = getNode(startValue);
        Node<T>* endNode = getNode(endValue);

        Stack<Node<T>*> s;
        s.push(startNode);

        while (!s.isEmpty()) {
            Node<T> *currentNode = s.top();
            s.pop();

            if(currentNode == endNode) {
                return true;
            }

            for (Node<T> *adjNode : currentNode->adjNodes) {
                if (!adjNode->visited) {
                    s.push(adjNode);
                    adjNode->visited = true;
                }
            }
        }

        for (Node<T>* node : nodes) {
            node->visited = false;
        }

        return false;
    }
};