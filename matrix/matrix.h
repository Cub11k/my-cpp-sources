#include <iostream>

#define NA_SUBMATRIX 1

class Matrix {
private:
    int M_;
    int N_;
    int* matrix_;

    Matrix();
public:
    Matrix(int M, int N);
    Matrix(const Matrix& obj);
    ~Matrix();
    void set_value(int i, int j, int value); 
    Matrix& operator= (const Matrix& matrix); 
    Matrix& operator+ (const Matrix& matr); 
    Matrix& operator- (const Matrix& matr);
    void print() const;
    int* get_obj(int line, int kollon);

    Matrix* submatrix_(int i, int j, int m, int n);
};

