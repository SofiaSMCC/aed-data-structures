#include <iostream>

struct Node
{
    int col;
    double value;
    Node *next;
    Node *prev;

    Node(int c, double val) : col(c), value(val), next(nullptr), prev(nullptr) {}
};

struct RowHeader
{
    int row;
    Node *rowHead;
    RowHeader *next;

    RowHeader(int r) : row(r), rowHead(nullptr), next(nullptr) {}
};

class SparseMatrix
{
private:
    RowHeader *head;

public:
    SparseMatrix() : head(nullptr) {}

    ~SparseMatrix()
    {
        RowHeader *currentRow = head;
        while (currentRow != nullptr)
        {
            Node *currentNode = currentRow->rowHead;
            if (currentNode != nullptr)
            {
                Node *startNode = currentNode;
                do
                {
                    Node *toDelete = currentNode;
                    currentNode = currentNode->next;
                    delete toDelete;
                } while (currentNode != startNode);
            }
            RowHeader *toDeleteRow = currentRow;
            currentRow = currentRow->next;
            delete toDeleteRow;
        }
    }

    void addValue(int row, int col, double value)
    {
        if (value == 0)
            return;

        RowHeader *currentRow = head;
        RowHeader *prevRow = nullptr;

        while (currentRow != nullptr && currentRow->row < row)
        {
            prevRow = currentRow;
            currentRow = currentRow->next;
        }

        if (currentRow == nullptr || currentRow->row > row)
        {
            RowHeader *newRow = new RowHeader(row);
            newRow->next = currentRow;
            if (prevRow == nullptr)
            {
                head = newRow;
            }
            else
            {
                prevRow->next = newRow;
            }
            currentRow = newRow;
        }

        Node *currentNode = currentRow->rowHead;
        Node *prevNode = nullptr;

        if (currentNode == nullptr)
        {
            Node *newNode = new Node(col, value);
            newNode->next = newNode;
            newNode->prev = newNode;
            currentRow->rowHead = newNode;
        }
        else
        {
            do
            {
                if (currentNode->col >= col)
                    break;
                prevNode = currentNode;
                currentNode = currentNode->next;
            } while (currentNode != currentRow->rowHead);

            if (currentNode != currentRow->rowHead || currentNode->col != col)
            {
                Node *newNode = new Node(col, value);
                if (prevNode == nullptr)
                {
                    newNode->next = currentNode;
                    newNode->prev = currentNode->prev;
                    currentNode->prev->next = newNode;
                    currentNode->prev = newNode;
                    currentRow->rowHead = newNode;
                }
                else
                {
                    newNode->next = currentNode;
                    newNode->prev = prevNode;
                    prevNode->next = newNode;
                    currentNode->prev = newNode;
                }
            }
            else
            {
                currentNode->value = value;
            }
        }
    }

    void printMatrix() const
    {
        RowHeader *currentRow = head;
        while (currentRow != nullptr)
        {
            Node *currentNode = currentRow->rowHead;
            if (currentNode != nullptr)
            {
                Node *startNode = currentNode;
                do
                {
                    std::cout << "Row: " << currentRow->row << ", Col: " << currentNode->col << ", Value: " << currentNode->value << std::endl;
                    currentNode = currentNode->next;
                } while (currentNode != startNode);
            }
            currentRow = currentRow->next;
        }
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
