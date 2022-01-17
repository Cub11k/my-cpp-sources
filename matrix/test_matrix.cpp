#include "matrix.h"

using namespace std;

int main() {
    Matrix A(2, 3);
    cout << "A:" << endl;
    A.print();

    A.set_value(0, 0, 1);
    A.set_value(0, 1, 2);
    A.set_value(0, 2, 8);
    A.set_value(1, 0, 1);
    A.set_value(1, 1, 0);
    A.set_value(1, 2, 7);
    cout << "A:" << endl;
    A.print();
    Matrix C(2, 2);
    Matrix B = A;
    cout << endl << "copied matrix B:" << endl;
    B.print();

    int* tmp = 0;
    pair <int, int> coords[3] = { {0, 2}, {1, 0}, {1, 2} };
    for (int i = 0; i < 3; ++i) {
        tmp = A.get_obj(coords[i].first, coords[i].second);
        if (tmp) {
            cout << "A[" << coords[i].first << "][" << coords[i].second << "] = " << *tmp << endl;
        } else {
            cout << "get_obj error" << endl;
        }
    }
    cout << endl;

    cout << "A:" << endl;
    A.print();

    Matrix* ptr = A.submatrix_(0, 0, 2, 2);
    if (ptr) {
        C = *ptr;
    } else {
        cout << "submatrix_ error" << endl;
        return NA_SUBMATRIX;
    }

    cout << "C:" << endl;
    C.print();
    A = A + B;
    cout << "A+B:" << "\n";
    A.print();
    return 0;
}