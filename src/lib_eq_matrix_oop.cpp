#include "lib_matrix_oop.h"

bool LibMatrix::EqMatrix(const LibMatrix& other) const noexcept {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    return false;
  }
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      if (fabs(matrix_[m][n] - other.matrix_[m][n]) > 1e-7) {
        return false;
      }
    }
  }
  return true;
}
