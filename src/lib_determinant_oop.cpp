#include "lib_matrix_oop.h"

double LibMatrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to compute determinant.");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  double det = 1.0;
  if (rows_) {
    LibMatrix Gaussian(*this);
    int r = rows_;
    int swapCount = 0;
    for (int i = 0; i < r; ++i) {
      double maxElement = std::abs(Gaussian(i, i));
      int maxRow = i;
      for (int k = i + 1; k < r; k++) {
        if (std::abs(Gaussian(k, i)) > maxElement) {
          maxElement = std::abs(Gaussian(k, i));
          maxRow = k;
        }
      }
      if (maxRow != i) {
        for (int k = i; k < r; k++) {
          std::swap(Gaussian(maxRow, k), Gaussian(i, k));
        }
        swapCount++;
      }
      if (std::abs(Gaussian(i, i)) < 1e-7) {
        det = 0;
        break;
      }
      det *= Gaussian(i, i);
      for (int k = i + 1; k < r; k++) {
        Gaussian(i, k) /= Gaussian(i, i);
      }
      for (int k = i + 1; k < r; k++) {
        double factor = Gaussian(k, i);
        for (int j = i + 1; j < r; j++) {
          Gaussian(k, j) -= Gaussian(i, j) * factor;
        }
      }
    }
    if (swapCount % 2 != 0) {
      det = -det;
    }
  }
  return det;
}
