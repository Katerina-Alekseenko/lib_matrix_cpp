#include "lib_matrix_oop.h"

LibMatrix LibMatrix::Transpose() const {
  LibMatrix Transpose(cols_, rows_);
  for (int m = 0; m < cols_; m++) {
    for (int n = 0; n < rows_; n++) {
      Transpose.matrix_[m][n] = matrix_[n][m];
    }
  }
  return Transpose;
}
