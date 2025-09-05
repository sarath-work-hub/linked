
#include <iostream>
using namespace std;

struct Node {
    int row, col, value;
    Node* next;
};

class SparseMatrix {
private:
    Node* head;
    int rows, cols;

public:
    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
        head = nullptr;
    }

    void insert(int r, int c, int val) {
        if (val == 0) return;

        Node* newNode = new Node{r, c, val, nullptr};

        if (!head || (r < head->row || (r == head->row && c < head->col))) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && (current->next->row < r ||
               (current->next->row == r && current->next->col < c))) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void display() {
        Node* current = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (current && current->row == i && current->col == j) {
                    cout << current->value << " ";
                    current = current->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    ~SparseMatrix() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    int r, c, num;
    cout << "Enter dimensions of the matrix (rows cols): ";
    cin >> r >> c;
    cout << "Enter number of non-zero elements: ";
    cin >> num;

    SparseMatrix sm(r, c);
    cout << "Enter row, column, and value for " << num << " non-zero elements:\n";
    for (int i = 0; i < num; i++) {
        int row, col, val;
        cin >> row >> col >> val;
        sm.insert(row, col, val);
    }

    cout << "\nSparse Matrix:\n";
    sm.display();
    return 0;
}
