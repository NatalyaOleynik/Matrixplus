#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(Constructors, DefaultConstructor) { ASSERT_NO_THROW(Matrix a); }

TEST(Constructors, ParamConstructor) {
  ASSERT_NO_THROW(Matrix a(2, 2));
  ASSERT_THROW(Matrix a(0, 2), std::invalid_argument);
}

TEST(Constructors, CopyConstructor) {
  Matrix a;
  ASSERT_NO_THROW(Matrix b(a));
}

TEST(Constructors, MoveConstructor) {
  Matrix a;
  ASSERT_NO_THROW(Matrix b(std::move(a)));
}

TEST(Acsessors, Getters) {
  Matrix a;
  ASSERT_TRUE(a.get_rows() == 3);
  ASSERT_TRUE(a.get_cols() == 3);
}

TEST(Acsessors, Setters_1) {
  Matrix a;
  a.set_rows(4);
  a.set_cols(5);
  ASSERT_TRUE(a.get_rows() == 4);
  ASSERT_TRUE(a.get_cols() == 5);
}

TEST(Acsessors, Setters_2) {
  Matrix a;
  ASSERT_THROW(a.set_rows(0), std::invalid_argument);
}

TEST(Operations, EqMatrix_1) {
  Matrix a;
  Matrix b;
  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(Operations, EqMatrix_2) {
  Matrix a;
  Matrix b(2, 3);
  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(Operations, EqMatrix_3) {
  Matrix a;
  Matrix b;
  a(0, 1) = 0.0000001;
  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(Operations, SumMatrix_1) {
  Matrix a(2, 2);
  Matrix b(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(0, 1) = 5.525;
  b(1, 0) = -6.525;
  b(1, 1) = -7.525;

  Matrix result(2, 2);
  result(0, 0) = 5.05;
  result(0, 1) = 7.05;
  result(1, 0) = -4.0;
  result(1, 1) = -4.0;

  a.SumMatrix(b);

  ASSERT_EQ(a, result);
}

TEST(Operations, SumMatrix_2) {
  Matrix a(2, 2);
  Matrix b(2, 1);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(1, 0) = -6.525;

  ASSERT_THROW(a.SumMatrix(b), std::invalid_argument);
}

TEST(Operations, SubMatrix_1) {
  Matrix a(2, 2);
  Matrix b(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(0, 1) = 5.525;
  b(1, 0) = -6.525;
  b(1, 1) = -7.525;

  Matrix result(2, 2);
  result(0, 0) = -4.0;
  result(0, 1) = -4.0;
  result(1, 0) = 9.05;
  result(1, 1) = 11.05;

  a.SubMatrix(b);

  ASSERT_EQ(a, result);
}

TEST(Operations, SubMatrix_2) {
  Matrix a(2, 2);
  Matrix b(2, 1);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(1, 0) = -6.525;

  ASSERT_THROW(a.SubMatrix(b), std::invalid_argument);
}

TEST(Operations, MulNumber_1) {
  Matrix a(2, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = -2.525;
  a(1, 1) = -3.525;

  Matrix result(2, 2);
  result(0, 0) = 2.625;
  result(0, 1) = 7.625;
  result(1, 0) = -12.625;
  result(1, 1) = -17.625;

  a.MulNumber(5.0);

  ASSERT_EQ(a, result);
}

TEST(Operations, MulNumber_2) {
  Matrix a(2, 2);
  Matrix b(std::move(a));

  ASSERT_THROW(a.MulNumber(5.0), std::out_of_range);
}

TEST(Operations, MulMatrix_1) {
  Matrix a(2, 3);
  Matrix b(3, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(0, 2) = 2.525;
  a(1, 0) = 3.525;
  a(1, 1) = 4.525;
  a(1, 2) = 5.525;

  b(0, 0) = 6.525;
  b(0, 1) = 7.525;
  b(1, 0) = -8.525;
  b(1, 1) = -9.525;
  b(2, 0) = -10.525;
  b(2, 1) = -11.525;

  Matrix result(2, 2);
  result(0, 0) = -36.150625;
  result(0, 1) = -39.675625;
  result(1, 0) = -73.725625;
  result(1, 1) = -80.250625;

  a.MulMatrix(b);

  ASSERT_EQ(a, result);
}

TEST(Operations, MulMatrix_2) {
  Matrix a(2, 3);
  Matrix b(2, 3);

  ASSERT_THROW(a.MulMatrix(b), std::invalid_argument);
}

TEST(Operations, Transpose_1) {
  Matrix a(3, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;
  a(2, 0) = 4.525;
  a(2, 1) = 5.525;

  Matrix result(2, 3);
  result(0, 0) = 0.525;
  result(0, 1) = 2.525;
  result(0, 2) = 4.525;
  result(1, 0) = 1.525;
  result(1, 1) = 3.525;
  result(1, 2) = 5.525;

  Matrix b = a.Transpose();

  ASSERT_EQ(b, result);
}

TEST(Operations, Transpose_2) {
  Matrix a(3, 2);
  Matrix b(std::move(a));

  ASSERT_THROW(Matrix b = a.Transpose(), std::out_of_range);
}

TEST(Operations, Determinant_1) {
  Matrix a(1, 1);
  a(0, 0) = 0.525;

  double result = 0.525;

  double b = a.Determinant();

  ASSERT_DOUBLE_EQ(b, result);
}

TEST(Operations, Determinant_2) {
  Matrix a(2, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  double result = -2.0;

  double b = a.Determinant();

  ASSERT_DOUBLE_EQ(b, result);
}

TEST(Operations, Determinant_3) {
  Matrix a;
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(0, 2) = 2.525;
  a(1, 0) = 3.525;
  a(1, 1) = 4.525;
  a(1, 2) = 5.525;
  a(2, 0) = 6.525;
  a(2, 1) = 7.525;
  a(2, 2) = 8.525;

  double result = 0.0;

  double b = a.Determinant();

  ASSERT_TRUE(std::fabs(result - b) < 1e-7);
}

TEST(Operations, Determinant_4) {
  Matrix a;
  Matrix b(std::move(a));

  ASSERT_THROW(a.Determinant(), std::out_of_range);
}

TEST(Operations, Determinant_5) {
  Matrix a(3, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;
  a(2, 0) = 4.525;
  a(2, 1) = 5.525;

  ASSERT_THROW(a.Determinant(), std::invalid_argument);
}

TEST(Operations, CalcComp_1) {
  Matrix a(1, 1);
  a(0, 0) = 0.525;

  Matrix result(1, 1);
  result(0, 0) = 1.0;

  Matrix b = a.CalcComplements();

  ASSERT_EQ(b, result);
}

TEST(Operations, CalcComp_2) {
  Matrix a(2, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  Matrix result(2, 2);
  result(0, 0) = 3.525;
  result(0, 1) = -2.525;
  result(1, 0) = -1.525;
  result(1, 1) = 0.525;

  Matrix b = a.CalcComplements();

  ASSERT_EQ(b, result);
}

TEST(Operations, CalcComp_3) {
  Matrix a(3, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;
  a(2, 0) = 4.525;
  a(2, 1) = 5.525;

  ASSERT_THROW(Matrix b = a.CalcComplements(), std::invalid_argument);
}

TEST(Operations, CalcComp_4) {
  Matrix a;
  Matrix b(std::move(a));

  ASSERT_THROW(a.CalcComplements(), std::out_of_range);
}

TEST(Operations, Inverse_1) {
  Matrix a(1, 1);
  a(0, 0) = 0.525;

  Matrix result(1, 1);
  result(0, 0) = 1.904762;

  Matrix b = a.InverseMatrix();

  ASSERT_EQ(b, result);
}

TEST(Operations, Inverse_2) {
  Matrix a(2, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  Matrix result(2, 2);
  result(0, 0) = -1.7625;
  result(0, 1) = 0.7625;
  result(1, 0) = 1.2625;
  result(1, 1) = -0.2625;

  Matrix b = a.InverseMatrix();

  ASSERT_EQ(b, result);
}

TEST(Operations, Inverse_3) {
  Matrix a;
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(0, 2) = 2.525;
  a(1, 0) = 3.525;
  a(1, 1) = 4.525;
  a(1, 2) = 5.525;
  a(2, 0) = 6.525;
  a(2, 1) = 7.525;
  a(2, 2) = 8.525;

  ASSERT_THROW(a.InverseMatrix(), std::range_error);
}

TEST(Operators, Sum_1) {
  Matrix a(2, 2);
  Matrix b(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(0, 1) = 5.525;
  b(1, 0) = -6.525;
  b(1, 1) = -7.525;

  Matrix result(2, 2);
  result(0, 0) = 5.05;
  result(0, 1) = 7.05;
  result(1, 0) = -4.0;
  result(1, 1) = -4.0;

  Matrix c(2, 2);
  c = a + b;

  ASSERT_EQ(c, result);
}

TEST(Operators, Sum_2) {
  Matrix a(2, 2);
  Matrix b(2, 1);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(1, 0) = -6.525;

  Matrix c;

  ASSERT_THROW(c = a + b, std::invalid_argument);
}

TEST(Operators, Sub_1) {
  Matrix a(2, 2);
  Matrix b(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(0, 1) = 5.525;
  b(1, 0) = -6.525;
  b(1, 1) = -7.525;

  Matrix result(2, 2);
  result(0, 0) = -4.0;
  result(0, 1) = -4.0;
  result(1, 0) = 9.05;
  result(1, 1) = 11.05;

  Matrix c(2, 2);
  c = a - b;

  ASSERT_EQ(c, result);
}

TEST(Operators, Sub_2) {
  Matrix a(2, 2);
  Matrix b(2, 1);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(1, 0) = -6.525;

  Matrix c;

  ASSERT_THROW(c = a - b, std::invalid_argument);
}

TEST(Operators, MulMatrix_1) {
  Matrix a(2, 3);
  Matrix b(3, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(0, 2) = 2.525;
  a(1, 0) = 3.525;
  a(1, 1) = 4.525;
  a(1, 2) = 5.525;

  b(0, 0) = 6.525;
  b(0, 1) = 7.525;
  b(1, 0) = -8.525;
  b(1, 1) = -9.525;
  b(2, 0) = -10.525;
  b(2, 1) = -11.525;

  Matrix result(2, 2);
  result(0, 0) = -36.150625;
  result(0, 1) = -39.675625;
  result(1, 0) = -73.725625;
  result(1, 1) = -80.250625;

  Matrix c(2, 2);
  c = a * b;

  ASSERT_EQ(c, result);
}

TEST(Operators, MulMatrix_2) {
  Matrix a(2, 3);
  Matrix b(2, 3);
  Matrix c;

  ASSERT_THROW(c = a * b, std::invalid_argument);
}

TEST(Operators, MulNumber_1) {
  Matrix a(2, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = -2.525;
  a(1, 1) = -3.525;

  Matrix result(2, 2);
  result(0, 0) = 2.625;
  result(0, 1) = 7.625;
  result(1, 0) = -12.625;
  result(1, 1) = -17.625;

  Matrix c(2, 2);
  c = a * 5.0;

  ASSERT_EQ(c, result);
}

TEST(Operators, MulNumber_2) {
  Matrix a(2, 2);
  Matrix b(std::move(a));

  Matrix c;

  ASSERT_THROW(c = a * 5.0, std::invalid_argument);
}

TEST(Operators, MulNumber_3) {
  Matrix a(2, 2);
  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = -2.525;
  a(1, 1) = -3.525;

  Matrix result(2, 2);
  result(0, 0) = 2.625;
  result(0, 1) = 7.625;
  result(1, 0) = -12.625;
  result(1, 1) = -17.625;

  Matrix c(2, 2);
  c = 5.0 * a;

  ASSERT_EQ(c, result);
}

TEST(Operators, Assig_1) {
  Matrix a(2, 2);
  Matrix b(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(0, 1) = 5.525;
  b(1, 0) = -6.525;
  b(1, 1) = -7.525;

  a = b;

  ASSERT_EQ(a, b);
}

TEST(Operators, Assig_2) {
  Matrix a(2, 3);
  Matrix b(3, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(0, 2) = 2.525;
  a(1, 0) = 3.525;
  a(1, 1) = 4.525;
  a(1, 2) = 5.525;

  b(0, 0) = 6.525;
  b(0, 1) = 7.525;
  b(1, 0) = -8.525;
  b(1, 1) = -9.525;
  b(2, 0) = -10.525;
  b(2, 1) = -11.525;

  a = b;

  ASSERT_EQ(a, b);
}

TEST(Operators, SumAssig_1) {
  Matrix a(2, 2);
  Matrix b(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(0, 1) = 5.525;
  b(1, 0) = -6.525;
  b(1, 1) = -7.525;

  Matrix result(2, 2);
  result(0, 0) = 5.05;
  result(0, 1) = 7.05;
  result(1, 0) = -4.0;
  result(1, 1) = -4.0;

  a += b;

  ASSERT_EQ(a, result);
}

TEST(Operators, SumAssig_2) {
  Matrix a(2, 2);
  Matrix b(2, 1);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(1, 0) = -6.525;

  ASSERT_THROW(a += b, std::invalid_argument);
}

TEST(Operators, SubAssig_1) {
  Matrix a(2, 2);
  Matrix b(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(0, 1) = 5.525;
  b(1, 0) = -6.525;
  b(1, 1) = -7.525;

  Matrix result(2, 2);
  result(0, 0) = -4.0;
  result(0, 1) = -4.0;
  result(1, 0) = 9.05;
  result(1, 1) = 11.05;

  a -= b;

  ASSERT_EQ(a, result);
}

TEST(Operators, SubAssig_2) {
  Matrix a(2, 2);
  Matrix b(2, 1);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = 2.525;
  a(1, 1) = 3.525;

  b(0, 0) = 4.525;
  b(1, 0) = -6.525;

  ASSERT_THROW(a -= b, std::invalid_argument);
}

TEST(Operators, MulAssig_1) {
  Matrix a(2, 3);
  Matrix b(3, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(0, 2) = 2.525;
  a(1, 0) = 3.525;
  a(1, 1) = 4.525;
  a(1, 2) = 5.525;

  b(0, 0) = 6.525;
  b(0, 1) = 7.525;
  b(1, 0) = -8.525;
  b(1, 1) = -9.525;
  b(2, 0) = -10.525;
  b(2, 1) = -11.525;

  Matrix result(2, 2);
  result(0, 0) = -36.150625;
  result(0, 1) = -39.675625;
  result(1, 0) = -73.725625;
  result(1, 1) = -80.250625;

  a *= b;

  ASSERT_EQ(a, result);
}

TEST(Operators, MulAssig_2) {
  Matrix a(2, 3);
  Matrix b(2, 3);

  ASSERT_THROW(a *= b, std::invalid_argument);
}

TEST(Operators, MulNumAssig_1) {
  Matrix a(2, 2);

  a(0, 0) = 0.525;
  a(0, 1) = 1.525;
  a(1, 0) = -2.525;
  a(1, 1) = -3.525;

  Matrix result(2, 2);
  result(0, 0) = 2.625;
  result(0, 1) = 7.625;
  result(1, 0) = -12.625;
  result(1, 1) = -17.625;

  a *= 5;

  ASSERT_EQ(a, result);
}

TEST(Operators, MulNumAssig_2) {
  Matrix a(2, 2);
  Matrix b(std::move(a));

  ASSERT_THROW(a *= 5.0, std::out_of_range);
}

TEST(Operators, Index_1) {
  const Matrix a;
  std::cout << a(1, 0) << std::endl;
}

TEST(Operators, Index_2) {
  Matrix a;
  a(1, 0) = 3.0;

  ASSERT_TRUE(a(1, 0) == 3.0);
}

TEST(Operators, Index_3) {
  Matrix a;
  ASSERT_THROW(a(3, 0) = 3.0, std::out_of_range);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}