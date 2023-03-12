// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#define ALLOC_ERROR "Error: bad allocation"
#define NUMBERS_ERROR "Error: rows and cols > 0"

using std::string;

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

class Matrix
{
 public:
  // parameters constructor
  /// \param rows the rows of the matrix
  /// \param cols the columns of the matrix
  Matrix(int rows,int cols)
  {
    if (rows < 1 || cols < 1)
      {
        std::cerr << NUMBERS_ERROR << std::endl;
        exit(EXIT_FAILURE);
      }
    _cols = cols;
    _rows = rows;
    int total_num = _rows * _cols;
    _table = new (std::nothrow)float[total_num];
    if (_table == nullptr)
      {
        std::cerr << ALLOC_ERROR << std::endl;
        exit(EXIT_FAILURE);
      }
    int i = 0;
    for(i = 0; i < total_num; i++)
      {
        _table[i] = 0;
      }
  }
  // default constructor
  Matrix()
  {
    _cols = 1;
    _rows = 1;
    _table = new (std::nothrow)float[sizeof (float)];
    if (_table == nullptr)
      {
        std::cerr << ALLOC_ERROR << std::endl;
        exit(EXIT_FAILURE);
      }
    _table[0] = 0;
  }
  // copy constructor
  /// \param other_mat the matrix to copy from
  Matrix(const Matrix& other_mat)
  {
    _cols = other_mat._cols;
    _rows = other_mat._rows;
    int total_num = _rows * _cols;
    _table = new (std::nothrow)float[total_num];
    if (_table == nullptr)
      {
        std::cerr << ALLOC_ERROR << std::endl;
        exit(EXIT_FAILURE);
      }
    int i = 0;
    for(i = 0; i < total_num; i++)
      {
        _table[i] = other_mat._table[i];
      }
  }
  //destructor
  ~Matrix()
  {
    delete[] _table;
  }
  // Methods
  //copy assignment operator "="
  Matrix& operator=(const Matrix& mat);
  // getters
  int get_rows() const{return _rows;};
  int get_cols() const{return _cols;};
  // prints a matrix
  void plain_print() const;
  // multiplies to matrices by dots
  Matrix dot(const Matrix& other_mat) const;
  // transposes a matrix
  Matrix& transpose();
  // turns a matrix into a or column vector
  Matrix& vectorize();
  // returns the norm of a matrix
  float norm() const;
  // Matrix multiplication
  Matrix operator*(const Matrix& other_mat) const;
  // Matrix * scalar
  Matrix operator*(float scalar) const;
  // Scalar * Matrix
  friend Matrix operator*(float scalar, Matrix& matrix);
  // matrix addition
  Matrix operator+(const Matrix& other_mat) const;
  // matrix addition by reference
  Matrix& operator+=(const Matrix& other_mat);
  // () operator that cannot change a matrix values
  float operator()(int row_inx, int col_inx) const;
  // () operator that can change a matrix values
  float& operator()(int row_inx, int col_inx);
  // [] operator that cannot change a matrix values
  float operator[](int element_inx) const;
  // [] operator that can change a matrix values
  float& operator[](int element_inx);
  // << operator to use for stream
  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
  // reads from a binary file
  friend void read_binary_file(std::istream &is, Matrix& matrix);
 private:
  int _rows;
  int _cols;
  float *_table = nullptr;
};

#endif //MATRIX_H
