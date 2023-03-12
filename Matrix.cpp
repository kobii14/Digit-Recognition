#include "Matrix.h"
#include <iostream>
#include <cmath>
#define MATCH_ERROR "Error: no match for b.rows and a.cols"
#define INDEX_ERROR "Error: index of rows / cols is out of range"
#define DOUBLE_ASTERISK "**"
#define GRAY_RANGE 0.1
#define FILE_ERROR "Error: file opening has failed"

/// copy assignment operator "="
/// \param mat a matrix to copy from
/// \return reference to the copied matrix
Matrix& Matrix::operator=(const Matrix& mat)
{
  if(this != &mat)
    {
      delete[] _table;
      _rows = mat._rows;
      _cols = mat._cols;
      int total_num = _rows * _cols;
      _table = new float[total_num];
      int i = 0;
      for(i = 0; i < total_num; i++)
        {
          _table[i] = mat._table[i];
        }
    }
  return *this;
}
// prints the given matrix
void Matrix::plain_print () const
{
  int i = 0;
  int j = 0;
  for (i = 0; i < _rows; i ++)
    {
      for (j = 0; j < _cols; j++)
        {
          std::cout << _table[i * _cols + j] << " ";
        }
      std::cout << std::endl;
    }
}
/// matrix multiplication
/// \param other_mat matrix to multiply
/// \return a new matrix the is the multiplication of 2 matrices
Matrix Matrix::operator*(const Matrix &other_mat) const
{
  if (_cols != other_mat._rows)
    {
      std::cerr << MATCH_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  Matrix c(_rows, other_mat._cols);
  int i = 0;
  int j = 0;
  int k = 0;
  float sum = 0;
  for (i = 0; i < _rows; i ++)
    {
      for (j = 0; j < other_mat._cols; j++)
        {
          for (k = 0; k < _cols; k++)
            {
              sum += (other_mat._table[k * other_mat._cols + j]) *
                  (this->_table[i * _cols + k]);
            }
          c._table[i * c._cols + j] = sum;
          sum = 0;
        }
    }
  return c;
}
/// transposes a matrix
/// \return reference to the transposed matrix
Matrix& Matrix::transpose ()
{
  int total_num = _rows * _cols;
  float *temp_table = nullptr;
  temp_table = new float[total_num];
  int l = 0;
  for(l = 0; l < total_num; l++)
    {
      temp_table[l] = 0;
    }
  int i = 0;
  int j = 0;
  for (i = 0; i < _cols; i++)
    {
      for (j = 0; j < _rows; j++)
        {
          temp_table[i * _rows + j] = _table[j * _cols + i];
        }
    }
  int k = 0;
  for (k = 0; k < total_num; k++)
    {
      _table[k] = temp_table[k];
    }
  delete[] temp_table;
  int temp = _cols;
  _cols = _rows;
  _rows = temp;
  return *this;
}
/// turns a matrix into a or column vector
/// \return reference to the vectorized vector
Matrix& Matrix::vectorize()
{
  _rows = _rows * _cols;
  _cols = 1;
  return *this;
}

/// \return the norm of a matrix
float Matrix::norm () const
{
  float sum_1 = 0;
  int i = 0;
  for (i = 0; i < (_cols * _rows); i++)
    {
      sum_1 += (_table[i] * _table[i]);
    }
  sum_1 = sqrtf(sum_1);
  return sum_1;
}
// multiplies to matrices by dots
/// \param other_mat the matrix to multiply with
/// \return a new matrix the is the dot multiplication of 2 matrices
Matrix Matrix::dot(const Matrix &other_mat) const
{
  if ((other_mat._rows != _rows) || (other_mat._cols != _cols))
    {
      std::cerr << MATCH_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  Matrix c(_rows, _cols);
  int i = 0;
  for (i = 0; i < (_cols * _rows); i++)
    {
      c._table[i] = (_table[i] * other_mat._table[i]);
    }
  return c;
}
// matrix addition
/// \param other_mat matrix to add
/// \return new matrix
Matrix Matrix::operator+(const Matrix& other_mat) const
{
  if ((other_mat._rows != _rows) || (other_mat._cols != _cols))
    {
      std::cerr << MATCH_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  Matrix c(_rows, _cols);
  int i = 0;
  for (i = 0; i < (_cols * _rows); i++)
    {
      c._table[i] = (_table[i] + other_mat._table[i]);
    }
  return c;
}
/// matrix addition with reference
/// \param other_mat matrix to add
/// \return reference to the additioned matrix
Matrix & Matrix::operator+=(const Matrix &other_mat)
{
  if ((other_mat._rows != _rows) || (other_mat._cols != _cols))
    {
      std::cerr << MATCH_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  int i = 0;
  float temp = 0;
  for (i = 0; i < (_cols * _rows); i++)
    {
      temp = _table[i];
      _table[i] = (temp + other_mat._table[i]);
    }
  return *this;
}
// Matrix * scalar
Matrix Matrix::operator* (float scalar) const
{
  Matrix c(_rows, _cols);
  int i = 0;
  for (i = 0; i < (_cols * _rows); i++)
    {
      c._table[i] = (_table[i] * scalar);
    }
  return c;
}
// Scalar * Matrix
Matrix operator*(float scalar, Matrix& matrix)
{
  Matrix c(matrix._rows, matrix._cols);
  int i = 0;
  for (i = 0; i < (matrix._cols * matrix._rows); i++)
    {
      c._table[i] = (matrix._table[i] * scalar);
    }
  return c;
}
// () operator that cannot change a matrix values
/// \param row_inx value row index
/// \param col_inx value col index
/// \return the value in the right index
float Matrix::operator() (int row_inx, int col_inx) const
{
  if (row_inx > _rows - 1 || row_inx < 0 || col_inx > _cols - 1 || col_inx < 0)
    {
      std::cerr << INDEX_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  return _table[_cols * row_inx + col_inx];
}
// () operator that can change a matrix values
/// \param row_inx value row index
/// \param col_inx value col index
/// \return the value in the right index
float& Matrix::operator() (int row_inx, int col_inx)
{
  if (row_inx > _rows - 1 || row_inx < 0 || col_inx > _cols - 1 || col_inx < 0)
    {
      std::cerr << INDEX_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  return _table[_cols * row_inx + col_inx];
}
///  [] operator that cannot change a matrix values
/// \param element_inx index of the returned value
/// \return the value in the right index
float Matrix::operator[] (int element_inx) const
{
  if (element_inx > (_rows * _cols - 1) || element_inx < 0)
    {
      std::cerr << INDEX_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  return _table[element_inx];
}
///  [] operator that can change a matrix values
/// \param element_inx index of the returned value
/// \return the value in the right index
float& Matrix::operator[] (int element_inx)
{
  if (element_inx > (_rows * _cols - 1) || element_inx < 0)
    {
      std::cerr << INDEX_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  return _table[element_inx];
}
// << operator to use for stream
/// \param os the stream type
/// \param matrix
/// \return the stream to output to
std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < matrix._rows; i++)
    {
      for (j = 0; j < matrix._cols; j++)
        {
          if (matrix(i,j) >= GRAY_RANGE)
            {
              os << "  ";
            }
          else
            {
              os << DOUBLE_ASTERISK;
            }
        }
      os << std::endl;
    }
  return os;
}
///  reads from a binary file
/// \param is input stream
/// \param matrix matrix to read to
void read_binary_file(std::istream &is, Matrix& matrix)
{
  int total = matrix._rows * matrix._cols * (int) sizeof(float);
  is.read((char *) matrix._table, total);
  if (!is.good ())
    {
      std::cerr <<  FILE_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
}

