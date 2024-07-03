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
        if (head == nullptr)
            return;

        Node *current = head;
        do
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        } while (current != head);
    }

    void addValue(int row, int col, double value)
    {
        if (value == 0)
        {
            return;
        }

        Node *newNode = new Node(row, col, value);

        if (head == nullptr)
        {
            head = newNode;
            head->next = head; // Make the list circular
            return;
        }

        Node *current = head;
        Node *prev = nullptr;

        do
        {
            if ((current->row > row) || (current->row == row && current->col > col))
            {
                break;
            }
            prev = current;
            current = current->next;
        } while (current != head);

        newNode->next = current;

        if (prev == nullptr)
        { // Insert at the beginning
            Node *tail = head;
            while (tail->next != head)
            {
                tail = tail->next;
            }
            tail->next = newNode;
            head = newNode;
        }
        else
        {
            prev->next = newNode;
        }
    }

    void printMatrix() const
    {
        if (head == nullptr)
            return;

        Node *current = head;
        do
        {
            std::cout << "Row: " << current->row << ", Col: " << current->col << ", Value: " << current->value << std::endl;
            current = current->next;
        } while (current != head);
    }
};

int main()
{
    SparseMatrix matrix;

    // Representación de la matriz dispersa en coordenadas
    int inputData[][3] = {
        {2, 3, 7},
        {5, 1, 5},
        {5, 4, 2},
        {7, 4, 9},
        {8, 1, 4},
        {8, 6, 6},
        {9, 3, 3}};

    int numEntries = sizeof(inputData) / sizeof(inputData[0]);

    // Transformar la matriz dispersa en representación enlazada circular
    for (int i = 0; i < numEntries; ++i)
    {
        int row = inputData[i][0];
        int col = inputData[i][1];
        double value = inputData[i][2];
        matrix.addValue(row, col, value);
    }

    // Imprimir la matriz enlazada circular
    matrix.printMatrix();

    return 0;
}
