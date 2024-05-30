#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node *prev;
    Node *next;

    Node() : prev(nullptr), prev(nullptr){};
};

template <typename T>
class DoubleLinkedList
{
    Node<T> *head;

public:
    DoubleLinkedList() : head(nullptr) {}
    T front() {}
    T back() {}
    void pushFront(T data) {}
    void pushBack(T data) {}
    void popFront() {}
    void popBack() {}
    T operator[](int i) {}
    bool empty() {}
    int size() {}
    void clear () {}
    void sort () {}
    void reverse () {}
    void print () {}
};

int main()
{
    return 0;
}