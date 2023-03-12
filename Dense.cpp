#include "Dense.h"
/// () operator that cannot change values and applies the layer on input
/// \param matrix the matrix to activate the layer on
/// \return output new matrix
Matrix Dense::operator() (const Matrix& matrix) const
{
  Matrix new_mat(matrix.get_rows(), matrix.get_rows());
  new_mat = _w * matrix + _bias;
  Activation action(_act_type);
  new_mat = action(new_mat);
  return new_mat;
}

