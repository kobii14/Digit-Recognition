#include "Activation.h"
#include <cmath>
///  () operator that applies activation function on input
/// \param matrix matrix activate functions on
/// \return a new matrix after activation
Matrix Activation::operator() (const Matrix &matrix) const
{
  Matrix new_mat(matrix.get_rows(), matrix.get_cols());
  int i = 0;
  float sum_of_exp = 0;
  int mat_length = new_mat.get_rows() * new_mat.get_cols();
  if (_act_type == RELU)
    {
      for (i = 0; i < mat_length; i++)
        {
          if (matrix[i] >= 0)
            {
              new_mat[i] = matrix[i];
            }
          else
            {
              new_mat[i] = 0;
            }
        }
    }
  else if (_act_type == SOFTMAX)
    {
      for (i = 0; i < mat_length; i++)
        {
          new_mat[i] = std::exp(matrix[i]);
          sum_of_exp += new_mat[i];
        }
      new_mat = new_mat * (1 / sum_of_exp);
    }
  return new_mat;
}

