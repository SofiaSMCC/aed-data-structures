#include <iostream>

struct Node
{
    int row;
    int col;
    double value;
    Node *next;

    Node(int r, int c, double val) : row(r), col(c), value(val), next(nullptr) {}
};

class SparseMatrix
{
private:
    int rows, cols;
    Node *head;

public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols), head(nullptr) {}

    ~SparseMatrix()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void setValue(int row, int col, double value)
    {
        if (row >= rows || col >= cols || row < 0 || col < 0)
        {
            throw std::out_of_range("Index out of range");
        }

        Node *current = head;
        Node *prev = nullptr;

        while (current != nullptr && (current->row < row || (current->row == row && current->col < col)))
        {
            prev = current;
            current = current->next;
        }

        if (current != nullptr && current->row == row && current->col == col)
        {
            if (value == 0)
            {
                if (prev == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
            }
            else
            {
                current->value = value;
            }
        }
        else
        {
            if (value != 0)
            {
                Node *newNode = new Node(row, col, value);
                newNode->next = current;

                if (prev == nullptr)
                {
                    head = newNode;
                }
                else
                {
                    prev->next = newNode;
                }
            }
        }
    }

    double getValue(int row, int col) const
    {
        if (row >= rows || col >= cols || row < 0 || col < 0)
        {
            throw std::out_of_range("Index out of range");
        }

        Node *current = head;
        while (current != nullptr)
        {
            if (current->row == row && current->col == col)
            {
                return current->value;
            }
            current = current->next;
        }

        return 0.0;
    }

    void printMatrix() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << "Row: " << current->row << ", Col: " << current->col << ", Value: " << current->value << std::endl;
            current = current->next;
        }
    }
};

int main()
{
    SparseMatrix matrix(5, 5);

    matrix.setValue(1, 2, 3.0);
    matrix.setValue(3, 4, 5.0);
    matrix.setValue(1, 2, 0.0); // Eliminar valor en (1, 2)

    std::cout << "Value at (1, 2): " << matrix.getValue(1, 2) << std::endl;
    std::cout << "Value at (3, 4): " << matrix.getValue(3, 4) << std::endl;

    matrix.printMatrix();

    return 0;
}
