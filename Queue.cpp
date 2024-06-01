#include <iostream>
#define MAX_Q_SIZE 10

template <typename T>
class Queue
{
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index, count;

public:
    Queue() : front_index(0), rear_index(0), count(0) {}

    bool isFull()
    {
        return count == MAX_Q_SIZE;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    T front()
    {
        return list[front_index];
    }

    void enqueue(T e)
    {
        if(isFull()) return;
        list[rear_index] = e;
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        count++;
    }

    T dequeue()
    {
        T item = list[front_index];
        front_index = (front_index + 1) % MAX_Q_SIZE;
        count--;
        return item;
    }

    int size()
    {
        return count;
    }

    friend std::ostream &operator<<(std::ostream &os, const Queue &q)
    {
        int index = q.front_index;
        for (int i = 0; i < q.count; i++)
        {
            os << q.list[index] << " ";
            index = (index + 1) % MAX_Q_SIZE;
        }
        return os;
    }
};
