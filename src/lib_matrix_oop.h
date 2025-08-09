#ifndef SRC_LIBRARY_MATRIX_OOP_H_
#define SRC_LIBRARY_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

class LibMatrix {
 public:
  LibMatrix();
  explicit LibMatrix(int rows, int cols);
  LibMatrix(const LibMatrix& other);
  LibMatrix(LibMatrix&& other) noexcept;
  ~LibMatrix();

  LibMatrix& operator=(const LibMatrix& other);
  LibMatrix& operator=(LibMatrix&& other) noexcept;

  bool EqMatrix(const LibMatrix& other) const noexcept;
  void SumMatrix(const LibMatrix& other);
  void SubMatrix(const LibMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const LibMatrix& other);
  LibMatrix Transpose() const;
  double Determinant() const;
  LibMatrix CalcComplements() const;
  LibMatrix InverseMatrix() const;

  friend LibMatrix operator+(LibMatrix A, const LibMatrix& B);
  friend LibMatrix operator-(LibMatrix A, const LibMatrix& B);
  friend LibMatrix operator*(LibMatrix A, const LibMatrix& B);
  friend LibMatrix operator*(LibMatrix A, const double num);
  friend LibMatrix operator*(const double num, LibMatrix A);
  friend bool operator==(const LibMatrix& A, const LibMatrix& B) noexcept;

  LibMatrix& operator+=(const LibMatrix& other);
  LibMatrix& operator-=(const LibMatrix& other);
  LibMatrix& operator*=(const LibMatrix& other);
  LibMatrix& operator*=(const double num);
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  void InitializeMatrix();
  void CheckMatrixSize() const;
  void CheckMatrixSize(const LibMatrix& other) const;
  void CopyMatrix(const LibMatrix& other);
  void FreeMatrix();
  void CreateMinorMatrix(const LibMatrix& other, int row, int col);
};

#endif  // SRC_LIBRARY_MATRIX_OOP_H_
