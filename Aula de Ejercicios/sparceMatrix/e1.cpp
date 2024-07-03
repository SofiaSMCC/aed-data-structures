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
    Node *head;

public:
    SparseMatrix() : head(nullptr) {}

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

    void addValue(int row, int col, double value)
    {
        if (value == 0)
        {
            return;
        }

        Node *newNode = new Node(row, col, value);

        if (head == nullptr || (head->row > row || (head->row == row && head->col > col)))
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *current = head;
        while (current->next != nullptr && (current->next->row < row || (current->next->row == row && current->next->col < col)))
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
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
    SparseMatrix matrix;

    // Representación de la matriz dispersa en coordenadas
    int inputData[][3] = {
        {2, 1, 3},
        {2, 2, 5},
        {2, 7, 9},
        {3, 7, 5},
        {4, 5, 5},
        {4, 9, 22},
        {6, 5, 5},
        {7, 2, 5},
        {7, 8, 5},
        {9, 9, 5}};

    int numEntries = sizeof(inputData) / sizeof(inputData[0]);

    // Transformar la matriz dispersa en representación enlazada
    for (int i = 0; i < numEntries; ++i)
    {
        int row = inputData[i][0];
        int col = inputData[i][1];
        double value = inputData[i][2];
        matrix.addValue(row, col, value);
    }

    // Imprimir la matriz enlazada
    matrix.printMatrix();

    return 0;
}
