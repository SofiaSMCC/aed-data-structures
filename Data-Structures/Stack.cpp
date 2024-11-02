#include <iostream>
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