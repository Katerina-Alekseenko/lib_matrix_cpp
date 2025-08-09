#include "lib_matrix_oop.h"

void LibMatrix::SubMatrix(const LibMatrix& other) {
  CheckMatrixSize(other);
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      matrix_[m][n] -= other.matrix_[m][n];
    }
  }
}
