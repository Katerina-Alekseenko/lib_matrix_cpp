#include "lib_matrix_oop.h"

LibMatrix::LibMatrix() : rows_(0), cols_(0), matrix_(nullptr) {}

LibMatrix::LibMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CheckMatrixSize();
  InitializeMatrix();
}

LibMatrix::LibMatrix(const LibMatrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CheckMatrixSize();
  InitializeMatrix();
  CopyMatrix(other);
}

LibMatrix::LibMatrix(LibMatrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_;
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

LibMatrix::~LibMatrix() { FreeMatrix(); }

void LibMatrix::InitializeMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void LibMatrix::CheckMatrixSize() const {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Error: Invalid dimensions for matrix.");
  }
}

void LibMatrix::CheckMatrixSize(const LibMatrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Error: Matrices must have the same size.");
  }
}

void LibMatrix::CopyMatrix(const LibMatrix& other) {
  for (int i = 0; i < rows_ && i < other.rows_; i++) {
    for (int j = 0; j < cols_ && j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void LibMatrix::FreeMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

int LibMatrix::GetRows() const { return rows_; }
int LibMatrix::GetCols() const { return cols_; }

void LibMatrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("Error: Invalid dimensions for matrix.");
  }
  LibMatrix temp(rows, cols_);
  temp.CopyMatrix(*this);
  std::swap(*this, temp);
}

void LibMatrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument("Error: Invalid dimensions for matrix.");
  }
  LibMatrix temp(rows_, cols);
  temp.CopyMatrix(*this);
  std::swap(*this, temp);
}

LibMatrix& LibMatrix::operator=(const LibMatrix& other) {
  if (this != &other) {
    FreeMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    InitializeMatrix();
    CopyMatrix(other);
  }
  return *this;
}

LibMatrix& LibMatrix::operator=(LibMatrix&& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

LibMatrix& LibMatrix::operator+=(const LibMatrix& other) {
  SumMatrix(other);
  return *this;
}

LibMatrix& LibMatrix::operator-=(const LibMatrix& other) {
  SubMatrix(other);
  return *this;
}

LibMatrix& LibMatrix::operator*=(const LibMatrix& other) {
  MulMatrix(other);
  return *this;
}

LibMatrix& LibMatrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

LibMatrix operator+(LibMatrix A, const LibMatrix& B) {
  A += B;
  return A;
}

LibMatrix operator-(LibMatrix A, const LibMatrix& B) {
  A -= B;
  return A;
}

LibMatrix operator*(LibMatrix A, const LibMatrix& B) {
  A *= B;
  return A;
}

LibMatrix operator*(LibMatrix A, const double num) {
  A *= num;
  return A;
}

LibMatrix operator*(const double num, LibMatrix A) {
  A *= num;
  return A;
}

bool operator==(const LibMatrix& A, const LibMatrix& B) noexcept {
  return A.EqMatrix(B);
}

double& LibMatrix::operator()(int row, int col) {
  if (!matrix_ || row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Error: Incorrect indexes of matrix!");
  }
  return matrix_[row][col];
}

const double& LibMatrix::operator()(int row, int col) const {
  if (!matrix_ || row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Error: Incorrect indexes of matrix!");
  }
  return matrix_[row][col];
}
