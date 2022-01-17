#include "matrix.h"

Matrix::Matrix(int M, int N) {
    M_ = M;
    N_ = N;
    matrix_ = new int[N_ * M_];
    for (int i = 0; i < M_ * N_; i++) {
        matrix_[i] = 0;
    }
}

Matrix::Matrix(const Matrix& matrix) {
    M_ = matrix.M_;
    N_ = matrix.N_;
    matrix_ = new int[M_ * N_];
    for (int i = 0; i < M_ * N_; ++i) {
        matrix_[i] = matrix.matrix_[i];
    }
}

Matrix::~Matrix() {
    delete[ ] matrix_;
    M_ = 0;
    N_ = 0;
}

Matrix& Matrix::operator= (const Matrix& matrix) {
    if (this == &matrix) return *this;

    if (this->M_ > 0) {
        delete[ ] this->matrix_;
    }
    this->M_ = matrix.M_;
    this->N_ = matrix.N_;
    this->matrix_ = new int[(M_ * N_)];

    for (int i = 0; i < M_ * N_; i++) {
        this->matrix_[i] = matrix.matrix_[i];

    }
    return *this;
}

Matrix& Matrix::operator+ (const Matrix& matr) {
    if (N_ != matr.N_ || M_ != matr.M_) {
        std::cout << "Not commute" << std::endl;
        return *this;
    }
    static Matrix tmp(this->M_, this->N_);
    tmp = *this;
    for (int i = 0; i < M_ * N_; i++) {
        tmp.matrix_[i] += matr.matrix_[i];
    }
    return tmp;
}

Matrix& Matrix::operator- (const Matrix& matr) {
    if (N_ != matr.N_ || M_ != matr.M_) {
        std::cout << "Not commute" << std::endl;
        return *this;
    }
    static Matrix tmp(this->M_, this->N_);
    tmp = *this;
    for (int i = 0; i < M_ * N_; i++) {
        tmp.matrix_[i] -= matr.matrix_[i];
    }
    return tmp;
}

int* Matrix::get_obj(int line, int kollon) {
    if (line > N_) {
        return nullptr;
    }
    return &matrix_[line * N_ + kollon];

}

void Matrix::set_value(int i, int j, int value) {
    if (i >= M_ || j >= N_) {
        return;
    }
    matrix_[i * N_ + j] = value;
}

void Matrix::print() const {
    std::cout << "rows: " << M_ << " cols: " << N_ << std::endl;

    for (int i = 0; i < M_; ++i) {
        for (int j = 0; j < N_; ++j) {
            std::cout << matrix_[i * N_ + j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Matrix* Matrix::submatrix_(int i_start, int j_start, int m, int n) {
    Matrix* ma = new Matrix(m - i_start, n - j_start);
    if (!((i_start >= M_) || (m > M_) || (j_start >= N_) || (n > N_))) {
        for (int i = i_start; i < m; i++) {
            for (int j = j_start; j < n; j++) {
                int* tmp = get_obj(i, j);
                if (tmp) {
                    ma->matrix_[i * n + j] = *tmp;
                } else {
                    std::cout << "get_obj error" << std::endl;
                    return nullptr;
                }
            }
        }
        return ma;
    }
    return nullptr;
}