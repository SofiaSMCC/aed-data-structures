#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node *prev;
    Node *next;

    Node() : prev(nullptr), next(nullptr){};
    Node(T val) : data(val), prev(nullptr), next(nullptr){};
};

template <typename T>
class DoubleLinkedList
{
    Node<T> *head;

public:
    DoubleLinkedList() : head(nullptr) {}

    T front()
    {
        return head->data;
    }

    T back()
    {
        Node<T> *temp = head;

        while (temp->next != nullptr)
            temp = temp->next;
        return temp->data;
    }

    void pushFront(T data)
    {
        auto *temp = new Node<T>;
        temp->data = data;
        temp->next = head;
        temp->prev = nullptr;

        if (head != nullptr)
            head->prev = temp;
        head = temp;
    }

    void pushBack(T data)
    {
        auto *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            newNode->prev = nullptr;
            head = newNode;
            return;
        }

        Node<T> *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }

    void popFront()
    {
        if (head == nullptr)
            return;

        Node<T> *temp = head;
        temp = temp->next;

        if (head != nullptr)
            head->prev = nullptr;
        delete temp;
    }

    void popBack()
    {
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return;
        }

        Node<T> *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
    }

    T operator[](int i)
    {
        Node<T> *temp = head;
        int tr = 0;

        while (tr != i)
        {
            temp = temp->next;
            ++tr;
        }
        return temp->data;
    }

    bool empty()
    {
        return head == nullptr;
    }

    int size()
    {
        int s = 0;

        Node<T> *temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
            ++s;
        }
        return s;
    }

    void clear()
    {
        while (!empty())
            popFront();
    }

    void sort()
    {
        Node<T> *temp = head;
        while (temp)
        {
            Node<T> *min = temp;
            Node<T> *r = temp->next;

            while (r)
            {
                if (min->data > r->data)
                    min = r;
                r = r->next;
            }

            T x = temp->data;
            temp->data = min->data;
            min->data = x;
            temp = temp->next;
        }
    }

    void reverse()
    {
        if (head == nullptr || head->next == nullptr)
            return;

        Node<T> *current = head;
        Node<T> *temp = nullptr;

        while (current != nullptr)
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr)
            head = temp->prev;
    }

    void print()
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};