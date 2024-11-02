#include <iostream>
using namespace std;

struct TreeNode
{
    int value;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

public:
    TreeNode(int value) : value(value) {}
};

class Stack
{
    struct StackNode
    {
        TreeNode *value;
        StackNode *next = nullptr;
        StackNode(TreeNode *val) : value(val) {}
    };

    StackNode *topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(TreeNode *val)
    {
        StackNode *newNode = new StackNode(val);
        if (topNode == nullptr)
            topNode = newNode;
        else
        {
            newNode->next = topNode;
            topNode = newNode;
        }
    }

    TreeNode *pop()
    {
        if (topNode == nullptr)
            return nullptr;

        TreeNode *tempTN = topNode->value;
        StackNode *tempStack = topNode;
        topNode = topNode->next;

        delete tempStack;
        return tempTN;
    }

    bool is_empty()
    {
        return topNode == nullptr;
    }

    StackNode *top()
    {
        return topNode;
    }
};

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node *frontPtr;
    Node *rearPtr;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr) {}

    void enqueue(T value)
    {
        Node *newNode = new Node(value);
        if (is_empty())
        {
            frontPtr = newNode;
            rearPtr = newNode;
        }
        else
        {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
    }

    T dequeue()
    {
        if (is_empty())
            return T();
        T value = frontPtr->data;
        Node *temp = frontPtr;
        frontPtr = frontPtr->next;
        delete temp;
        return value;
    }

    bool is_empty()
    {
        return frontPtr == nullptr;
    }

    size_t size() const
    {
        size_t size = 0;
        Node *current = frontPtr;
        while (current != nullptr)
        {
            size++;
            current = current->next;
        }
        return size;
    }

    ~Queue()
    {
        while (!is_empty())
            dequeue();
    }
};

TreeNode *newNode(int value)
{
    TreeNode *temp = new TreeNode(value);
    return temp;
}

void insert(TreeNode *&root, int val)
{
    if (root == nullptr)
    {
        root = new TreeNode(val);
        return;
    }
    if (val < root->value)
        insert(root->left, val);
    else
        insert(root->right, val);
}

bool search(TreeNode *root, int val)
{
    if (root == nullptr)
        return false;

    if (root->value == val)
        return true;
    else if (val < root->value)
        return search(root->left, val);
    else
        return search(root->right, val);
}

void inorder(TreeNode *root)
{
    if (root != nullptr)
    {
        inorder(root->left);
        cout << root->value << " ";
        inorder(root->right);
    }
}

void preorder(TreeNode *root)
{
    if (root != nullptr)
    {
        cout << root->value << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode *root)
{
    if (root != nullptr)
    {
        preorder(root->left);
        preorder(root->right);
        cout << root->value << " ";
    }
}

class BST
{
    TreeNode *root = nullptr;

public:
    BST() {}

    void setRoot(TreeNode *node)
    {
        root = node;
    }

    TreeNode *insertNode(TreeNode *node, int val)
    {
        if (node == nullptr)
            return new TreeNode(val);
        if (val < node->value)
            node->left = insertNode(node->left, val);
        else if (val > node->value)
            node->right = insertNode(node->right, val);
        return node;
    }

    void insert(int value)
    {
        root = insertNode(root, value);
    }

    void BreadthFirstSearch_stack()
    {
        Stack stack;
        stack.push(root);

        while (!stack.is_empty())
        {
            Stack tempStack;
            while (!stack.is_empty())
            {
                TreeNode *node = stack.pop();
                cout << node->value << " ";
                if (node->left != nullptr)
                    tempStack.push(node->left);
                if (node->right != nullptr)
                    tempStack.push(node->right);
            }
            while (!tempStack.is_empty())
                stack.push(tempStack.pop());
        }
    }

    void BreadthFirstSearch_queue()
    {
        if (root == nullptr)
            return;

        Queue<TreeNode *> q;
        q.enqueue(root);

        while (!q.is_empty())
        {
            TreeNode *current = q.dequeue();
            cout << current->value << " ";

            if (current->left != nullptr)
                q.enqueue(current->left);
            if (current->right != nullptr)
                q.enqueue(current->right);
        }
    }

    void DepthFirstSearch()
    {
        if (root == nullptr)
            return;

        Stack stack;
        stack.push(root);

        while (!stack.is_empty())
        {
            TreeNode *current = stack.pop();
            cout << current->value << " ";

            if (current->right != nullptr)
                stack.push(current->right);
            if (current->left != nullptr)
                stack.push(current->left);
        }
    }

    void printByLevel()
    {
        if (root == nullptr)
            return;

        Queue<TreeNode *> q;
        q.enqueue(root);

        while (!q.is_empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i)
            {
                TreeNode *current = q.dequeue();
                cout << current->value << " ";

                if (current->left != nullptr)
                    q.enqueue(current->left);
                if (current->right != nullptr)
                    q.enqueue(current->right);
            }
            cout << endl;
        }
    }
};