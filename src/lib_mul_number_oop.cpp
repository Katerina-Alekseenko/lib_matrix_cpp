#include "lib_matrix_oop.h"

void LibMatrix::MulNumber(const double number) {
  if (!matrix_) {
    throw std::runtime_error("Error: Matrix is nullptr.");
  }
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      matrix_[m][n] *= number;
      if (std::isinf(matrix_[m][n]) || std::isnan(matrix_[m][n])) {
        throw std::runtime_error(
            "Error: Matrix contains Inf or NaN after multiplication.");
      }
    }
  }
}
