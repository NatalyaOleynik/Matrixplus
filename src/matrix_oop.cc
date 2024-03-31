#include "matrix_oop.h"

// Constructors

Matrix::Matrix() : Matrix(3, 3) {}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument(
        "The number of rows and columns must be greater than 0");
  MatrixMemoryAllocation();
}

Matrix::Matrix(const Matrix& other) : Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

// Accessors and mutators

int Matrix::get_rows() const noexcept { return rows_; }
int Matrix::get_cols() const noexcept { return cols_; }

void Matrix::set_rows(int rows) {
  CheckNumber(rows);
  if (rows_ != rows) {
    Matrix temp(rows, cols_);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols_; ++j) {
        temp.matrix_[i][j] = (i < rows_ ? matrix_[i][j] : 0);
      }
    }
    Swap(temp);
  }
}

void Matrix::set_cols(int cols) {
  CheckNumber(cols);
  if (cols_ != cols) {
    Matrix temp(rows_, cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols; ++j) {
        temp.matrix_[i][j] = (j < cols_ ? matrix_[i][j] : 0);
      }
    }
    Swap(temp);
  }
}

// Public methods

bool Matrix::EqMatrix(const Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if ((std::fabs(matrix_[i][j] - other.matrix_[i][j])) >= 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  CheckSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  CheckSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) {
  CheckMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }
  Swap(result);
}

Matrix Matrix::Transpose() const {
  CheckMatrix();
  Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

double Matrix::Determinant() const {
  CheckMatrix();
  CheckSize();
  double result = 0.0;
  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  else if (rows_ >= 3) {
    for (int j = 0; j < cols_; ++j) {
      double det = MinorMatrix(0, j).Determinant();
      result += std::pow(-1, j) * matrix_[0][j] * det;
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() const {
  CheckMatrix();
  CheckSize();
  Matrix result(rows_, cols_);
  if (rows_ == 1)
    result.matrix_[0][0] = 1;
  else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        double det = MinorMatrix(i, j).Determinant();
        result.matrix_[i][j] = std::pow(-1, i + j) * det;
      }
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() const {
  double det = Determinant();
  if (std::fabs(det) < 1e-7) throw std::range_error("Matrix determinant is 0");
  Matrix result = CalcComplements().Transpose();
  result.MulNumber(1 / det);
  return result;
}

// Overload operators

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

Matrix operator*(Matrix& other, const double num) {
  Matrix result(other);
  result.MulNumber(num);
  return result;
}

Matrix operator*(const double num, Matrix& other) {
  Matrix result(other);
  result.MulNumber(num);
  return result;
}

bool Matrix::operator==(const Matrix& other) const noexcept {
  return EqMatrix(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
  Matrix temp(other);
  Swap(temp);
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  Matrix temp(std::move(other));
  Swap(temp);
  return *this;
}

void Matrix::operator+=(const Matrix& other) { SumMatrix(other); }

void Matrix::operator-=(const Matrix& other) { SubMatrix(other); }

void Matrix::operator*=(const Matrix& other) { MulMatrix(other); }

void Matrix::operator*=(const double num) { MulNumber(num); }

double& Matrix::operator()(int i, int j) {
  CheckIndex(i, j);
  return matrix_[i][j];
}

const double& Matrix::operator()(int i, int j) const {
  CheckIndex(i, j);
  return matrix_[i][j];
}

// Private methods

void Matrix::MatrixMemoryAllocation() {
  matrix_ = new double* [rows_] {};
  if (!matrix_)
    throw std::out_of_range("No memory allocated");
  else {
    for (int i = 0; i < rows_;) {
      matrix_[i] = new double[cols_]{};
      if (!matrix_[i]) {
        for (int j = i; j >= 0; --j) {
          delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
        throw std::out_of_range("No memory allocated");
      } else
        ++i;
    }
  }
}

void Matrix::CheckMatrix() const {
  if (!matrix_ || rows_ <= 0 || cols_ <= 0)
    throw std::out_of_range("Incorrect matrix");
}

void Matrix::CheckNumber(int number) const {
  if (number <= 0) {
    throw std::invalid_argument(
        "The number of rows or columns must be greater than 0");
  }
}

void Matrix::CheckSize(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Different matrix dimensions");
}

void Matrix::CheckSize() const {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");
}

void Matrix::CheckIndex(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::out_of_range("Index is outside the matrix");
}

void Matrix::Swap(Matrix& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

Matrix Matrix::MinorMatrix(int rows, int cols) const noexcept {
  Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; ++i) {
    if (i == rows) continue;
    for (int j = 0; j < cols_; ++j) {
      if (j == cols) continue;
      result.matrix_[i < rows ? i : i - 1][j < cols ? j : j - 1] =
          matrix_[i][j];
    }
  }
  return result;
}
