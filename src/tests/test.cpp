#include <gtest/gtest.h>

#include "../lib_matrix_oop.h"

TEST(Constructors, DefaultConstructor) {
  LibMatrix A;
  EXPECT_EQ(A.GetRows(), 0);
  EXPECT_EQ(A.GetCols(), 0);
}

TEST(Constructors, InvalidMatrixSize) {
  EXPECT_THROW(LibMatrix A(0, 1), std::invalid_argument);
}

TEST(Constructors, ParametrizedConstructor) {
  LibMatrix A(2, 2), B(1, 1);
  EXPECT_EQ(A.GetCols(), 2);
  EXPECT_EQ(A.GetRows(), 2);
  EXPECT_EQ(B.GetCols(), 1);
  EXPECT_EQ(B.GetRows(), 1);
}

TEST(Constructors, DefaultConstructorCopy) {
  LibMatrix A;
  EXPECT_THROW(LibMatrix B(A), std::invalid_argument);
}

TEST(Constructors, CopyConstructor) {
  LibMatrix A(2, 3);
  LibMatrix B(A);
  EXPECT_EQ(B.GetRows(), 2);
  EXPECT_EQ(B.GetCols(), 3);
}

TEST(Constructors, CopyWithValues) {
  LibMatrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  LibMatrix B(A);
  EXPECT_TRUE(A.EqMatrix(B));
  EXPECT_TRUE(B.EqMatrix(A));
  B(0, 0) = 10;
  EXPECT_NE(B(0, 0), A(0, 0));
  EXPECT_EQ(A(0, 0), 1);
}

TEST(Constructors, MoveConstructor) {
  LibMatrix A(3, 4);
  LibMatrix B(A);
  LibMatrix C(std::move(A));
  EXPECT_EQ(C.GetRows(), 3);
  EXPECT_EQ(C.GetCols(), 4);
  EXPECT_EQ(A.GetRows(), 0);
  EXPECT_EQ(A.GetCols(), 0);
}

TEST(Mutators, SetRows_SetCols) {
  LibMatrix A(1, 1);
  A.SetRows(2);
  A.SetCols(3);
  EXPECT_EQ(A.GetRows(), 2);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(Mutators, NegativeRows) {
  LibMatrix A(1, 1);
  EXPECT_THROW(A.SetRows(-4), std::invalid_argument);
}

TEST(Mutators, NegativeCols) {
  LibMatrix A(1, 1);
  EXPECT_THROW(A.SetCols(-4), std::invalid_argument);
}

TEST(Operators, Assignment) {
  LibMatrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  LibMatrix B = A;
  LibMatrix C;
  C = B;
  LibMatrix D(1, 1);
  D = A;
  EXPECT_TRUE(A.EqMatrix(B) && A.EqMatrix(C) && A.EqMatrix(D));
  B(0, 0) = 10;
  EXPECT_NE(B(0, 0), A(0, 0));
  EXPECT_EQ(A(0, 0), 1);
}

TEST(Operators, Brackets) {
  LibMatrix A(1, 1);
  A(0, 0) = 1.;
  const LibMatrix AC = A;

  EXPECT_DOUBLE_EQ(AC(0, 0), 1.);
  EXPECT_DOUBLE_EQ(A.Determinant(), 1.);
  EXPECT_DOUBLE_EQ(A(0, 0), 1.);
}

TEST(Operators, BracketsOutOfRange) {
  LibMatrix A(1, 1);
  EXPECT_THROW(A(1, 2), std::out_of_range);
}

TEST(Operators, ConstBracketsOutOfRange) {
  LibMatrix A(1, 1);
  const LibMatrix AC = A;
  EXPECT_THROW(AC(1, 2), std::out_of_range);
}

TEST(Operators, SumSubMulEq) {
  LibMatrix A(3, 3);
  LibMatrix B(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
      B(i, j) = 2;
    }
  }
  LibMatrix result = A + B;
  A.SumMatrix(B);
  EXPECT_TRUE(A.EqMatrix(result));

  A.SubMatrix(B);
  result = result - B;
  EXPECT_TRUE(A.EqMatrix(result));
  result = A * B;
  A.MulMatrix(B);
  EXPECT_TRUE(A.EqMatrix(result));
  result *= 3.14;
  A.MulNumber(3.14);
  EXPECT_TRUE(A.EqMatrix(result));
  if (result == A) result = B;
  A = 2 * result;
  B.MulNumber(2);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrix, Equal) {
  LibMatrix A(2, 2);
  LibMatrix B(2, 2);

  A(0, 0) = 1.01;
  A(0, 1) = 2;
  A(1, 0) = 3.05;
  A(1, 1) = 4;
  B(0, 0) = 1.01;
  B(0, 1) = 2;
  B(1, 0) = 3.05;
  B(1, 1) = 4;
  EXPECT_EQ(A.EqMatrix(B), true);
}

TEST(EqMatrix, NotEqual) {
  LibMatrix A(3, 3);
  LibMatrix B(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
      B(i, j) = 2;
    }
  }
  EXPECT_EQ(A.EqMatrix(B), false);
}

TEST(EqMatrix, DifferentSizes) {
  LibMatrix A(3, 3);
  LibMatrix B(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 1;
    }
  }
  EXPECT_EQ(A.EqMatrix(B), false);
}

TEST(EqMatrix, DifferentSizes2) {
  LibMatrix A(4, 3);
  LibMatrix B(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 1;
    }
  }
  EXPECT_EQ(A.EqMatrix(B), false);
}

TEST(SumMatrix, OnePlusTwo) {
  LibMatrix A(3, 3);
  LibMatrix B(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
      B(i, j) = 2;
    }
  }
  A.SumMatrix(B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), 3);
    }
  }
}

TEST(SumMatrix, DifferentSizes) {
  LibMatrix A(3, 3);
  LibMatrix B(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(A.SumMatrix(B));
}

TEST(SumMatrix, DifferentSizes2) {
  LibMatrix A(4, 3);
  LibMatrix B(4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(A.SumMatrix(B));
}

TEST(SumMatrix, OnePlusZero) {
  LibMatrix A(3, 3);
  LibMatrix B(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  A.SumMatrix(B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), 1);
    }
  }
}

TEST(SubMatrix, OneMinusTwo) {
  LibMatrix A(3, 3);
  LibMatrix B(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
      B(i, j) = 2;
    }
  }
  A.SubMatrix(B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), -1);
    }
  }
}

TEST(SubMatrix, DifferentSizes) {
  LibMatrix A(3, 3);
  LibMatrix B(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(A.SubMatrix(B));
}

TEST(SubMatrix, DifferentSizes2) {
  LibMatrix A(4, 3);
  LibMatrix B(4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(A.SubMatrix(B));
}

TEST(SubMatrix, OneMinusZero) {
  LibMatrix A(3, 3);
  LibMatrix B(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 1;
    }
  }
  A.SubMatrix(B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), 1);
    }
  }
}

TEST(MulNumber, MulBy2) {
  LibMatrix A(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 2;
    }
  }
  A.MulNumber(2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), 4);
    }
  }
}

TEST(MulNumber, MulByZero) {
  LibMatrix A(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 2;
    }
  }
  A.MulNumber(0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), 0);
    }
  }
}

TEST(MulNumber, Inf) {
  double inf = INFINITY;
  LibMatrix A(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(A.MulNumber(inf));
}

TEST(MulNumber, Nan) {
  double quiet_nan = std::numeric_limits<double>::quiet_NaN();
  LibMatrix A(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(A.MulNumber(quiet_nan));
}

TEST(MulNumber, NanInfMatrix) {
  LibMatrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = std::numeric_limits<double>::infinity();
  A(1, 0) = 3.0;
  A(1, 1) = std::numeric_limits<double>::quiet_NaN();

  EXPECT_ANY_THROW(A.MulNumber(2.0));
}

TEST(MulNumber, Nullptr) {
  LibMatrix A = LibMatrix();
  EXPECT_ANY_THROW(A.MulNumber(2));
}

TEST(MulMatrix, CompatibleMatrices) {
  LibMatrix A(3, 3);
  LibMatrix B(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 2;
      B(i, j) = 4;
    }
  }
  A.MulMatrix(B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), 24);
    }
  }
}

TEST(MulMatrix, IncompatibleMatricesSize) {
  LibMatrix A(3, 4);
  LibMatrix B(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = 2;
      B(i, j) = 4;
    }
  }
  EXPECT_ANY_THROW(A.MulMatrix(B));
}

TEST(MulMatrix, ResultMatrixSizeCheck) {
  LibMatrix A(3, 4);
  LibMatrix B(4, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = 2;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      B(i, j) = 4;
    }
  }
  A.MulMatrix(B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), 32);
    }
  }
  EXPECT_EQ(A.GetCols(), 3);
  EXPECT_EQ(A.GetRows(), 3);
}

TEST(MulMatrix, Nullptr) {
  LibMatrix A = LibMatrix();
  ;
  LibMatrix B(3, 3);

  EXPECT_ANY_THROW(A.MulMatrix(B));
}

TEST(MulMatrix, Nullptr2) {
  LibMatrix A(3, 3);
  LibMatrix B = LibMatrix();

  EXPECT_ANY_THROW(A.MulMatrix(B));
}

TEST(MulMatrix, NanInfMatrix) {
  LibMatrix A(2, 2);
  LibMatrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = std::numeric_limits<double>::infinity();
  A(1, 0) = 3.0;
  A(1, 1) = std::numeric_limits<double>::quiet_NaN();

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      B(i, j) = 4;
    }
  }
  EXPECT_ANY_THROW(A.MulMatrix(B));
}

TEST(Transpose, Normal) {
  LibMatrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 3;
  A(1, 0) = 5;
  A(1, 1) = 7;
  A(2, 0) = 9;
  A(2, 1) = 10;

  LibMatrix B = A.Transpose();
  EXPECT_DOUBLE_EQ(B.GetRows(), 2);
  EXPECT_DOUBLE_EQ(B.GetCols(), 3);
  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(0, 1), 5);
  EXPECT_DOUBLE_EQ(B(0, 2), 9);
  EXPECT_DOUBLE_EQ(B(1, 0), 3);
  EXPECT_DOUBLE_EQ(B(1, 1), 7);
  EXPECT_DOUBLE_EQ(B(1, 2), 10);
}

TEST(Transpose, Nullptr) {
  LibMatrix A;
  EXPECT_ANY_THROW(A.Transpose());
}

TEST(Determinant, MatrixNotSquare) {
  LibMatrix A(3, 4);
  EXPECT_ANY_THROW(A.Determinant());
}

TEST(Determinant, ZeroDet) {
  LibMatrix A(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = count;
      count++;
    }
  }
  EXPECT_DOUBLE_EQ(A.Determinant(), 0);
}

TEST(Determinant, 5x5Matrix) {
  LibMatrix A(5, 5);
  A(0, 1) = 6;
  A(0, 2) = -2;
  A(0, 3) = -1;
  A(0, 4) = 5;

  A(1, 3) = -9;
  A(1, 4) = -7;
  A(2, 1) = 15;
  A(2, 2) = 35;

  A(3, 1) = -1;
  A(3, 2) = -11;
  A(3, 3) = -2;
  A(3, 4) = 1;

  A(4, 0) = -2;
  A(4, 1) = -2;
  A(4, 2) = 3;
  A(4, 4) = -2;
  EXPECT_NEAR(2480, A.Determinant(), 1e-7);
}

TEST(Determinant, 4x4Matrix) {
  LibMatrix A(4, 4);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 4;

  A(1, 0) = 1;
  A(1, 1) = 2;
  A(1, 2) = 5;
  A(1, 3) = 7;

  A(2, 0) = 1;
  A(2, 1) = 0;
  A(2, 2) = 6;
  A(2, 3) = 8;

  A(3, 0) = 1;
  A(3, 1) = 0;
  A(3, 2) = 6;
  A(3, 3) = 6;
  EXPECT_EQ(A.Determinant(), -8);
}

TEST(Determinant, 3x3Matrix) {
  LibMatrix A(3, 3);
  A(0, 0) = 5;
  A(0, 1) = 3;
  A(0, 2) = 1;

  A(1, 0) = 1;
  A(1, 1) = 4;
  A(1, 2) = 6;

  A(2, 0) = 0;
  A(2, 1) = 5;
  A(2, 2) = 9;

  EXPECT_NEAR(8, A.Determinant(), 1e-7);
}

TEST(Determinant, 2x2Matrix) {
  LibMatrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  EXPECT_EQ(A.Determinant(), -2);
}

TEST(Determinant, 1x1Matrix) {
  LibMatrix A(1, 1);
  A(0, 0) = 2.0;
  EXPECT_EQ(A.Determinant(), 2);
}

TEST(Determinant, ZeroMatrix) {
  LibMatrix A;
  EXPECT_EQ(A.Determinant(), 1);
}

TEST(CalcComplements, 3x3Matrix) {
  LibMatrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;

  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;

  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;

  A = A.CalcComplements();

  EXPECT_EQ(A(0, 0), 0);
  EXPECT_EQ(A(0, 1), 10);
  EXPECT_EQ(A(0, 2), -20);
  EXPECT_EQ(A(1, 0), 4);
  EXPECT_EQ(A(1, 1), -14);
  EXPECT_EQ(A(1, 2), 8);
  EXPECT_EQ(A(2, 0), -8);
  EXPECT_EQ(A(2, 1), -2);
  EXPECT_EQ(A(2, 2), 4);
}

TEST(CalcComplements, 1x1Matrix) {
  LibMatrix A(1, 1);
  LibMatrix B;
  A(0, 0) = 21;
  B = A.CalcComplements();
  EXPECT_EQ(B(0, 0), 21);
}

TEST(CalcComplements, NotSquare) {
  LibMatrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;

  A(1, 0) = 0;
  A(1, 1) = 4;

  A(2, 0) = 5;
  A(2, 1) = 2;

  EXPECT_ANY_THROW(A.CalcComplements());
}

TEST(InverseMatrix, 3x3Matrix) {
  LibMatrix A(3, 3);
  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 7;
  A(1, 0) = 6;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 5;
  A(2, 1) = -2;
  A(2, 2) = -3;

  LibMatrix matrix_res(3, 3);
  matrix_res(0, 0) = 1;
  matrix_res(0, 1) = -1;
  matrix_res(0, 2) = 1;
  matrix_res(1, 0) = -38;
  matrix_res(1, 1) = 41;
  matrix_res(1, 2) = -34;
  matrix_res(2, 0) = 27;
  matrix_res(2, 1) = -29;
  matrix_res(2, 2) = 24;

  LibMatrix B = A.InverseMatrix();
  EXPECT_TRUE(B.EqMatrix(matrix_res));
}

TEST(InverseMatrix, 1x1Matrix) {
  LibMatrix A(1, 1);
  A(0, 0) = 2.0;
  LibMatrix B = A.InverseMatrix();
  EXPECT_EQ(B(0, 0), 0.5);
}

TEST(InverseMatrix, 1x1Singular) {
  LibMatrix A(1, 1);
  A(0, 0) = 0.;
  EXPECT_ANY_THROW(A.InverseMatrix());
}

TEST(InverseMatrix, 3x3Singular) {
  LibMatrix A(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = count;
      count++;
    }
  }
  EXPECT_ANY_THROW(A.InverseMatrix());
}

TEST(InverseMatrix, NotSquare) {
  LibMatrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;

  A(1, 0) = 0;
  A(1, 1) = 4;

  A(2, 0) = 5;
  A(2, 1) = 2;

  EXPECT_ANY_THROW(A.InverseMatrix());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
