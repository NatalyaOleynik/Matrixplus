#ifndef SRC_MATRIX_OOP_H_
#define SRC_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

class Matrix {
 public:
  Matrix();                         // Default constructor
  Matrix(int rows, int cols);       // Parametrized constructor
  Matrix(const Matrix& other);      // Copy constructor
  Matrix(Matrix&& other) noexcept;  // Move constructor
  ~Matrix();                        // Destructor

  // accessors and mutators
  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(int rows);
  void set_cols(int cols);

  // public methods
  bool EqMatrix(const Matrix& other) const noexcept;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;

  // overload operators
  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  friend Matrix operator*(Matrix& other, const double num);
  friend Matrix operator*(const double num, Matrix& other);
  bool operator==(const Matrix& other) const noexcept;
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept;
  void operator+=(const Matrix& other);
  void operator-=(const Matrix& other);
  void operator*=(const Matrix& other);
  void operator*=(const double num);
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

 private:
  //  attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

  // private methods
  void MatrixMemoryAllocation();
  void CheckMatrix() const;
  void CheckNumber(int number) const;
  void CheckSize(const Matrix& other) const;
  void CheckSize() const;
  void CheckIndex(int i, int j) const;
  void Swap(Matrix& other) noexcept;
  Matrix MinorMatrix(int rows, int cols) const noexcept;
};

#endif  // SRC_MATRIX_OOP_H_