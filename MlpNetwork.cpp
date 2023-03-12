#include "MlpNetwork.h"
/// applies the entire network on input
/// \param matrix to apply the network on
/// \return digit struct
digit MlpNetwork::operator() (const Matrix &matrix) const
{
  Matrix new_matrix =
      layer_4(layer_3(layer_2(layer_1(matrix))));
  digit new_digit;
  int i = 0;
  int index = 0;
  float probability = 0;
  for (i = 0; i < new_matrix.get_cols() * new_matrix.get_rows(); i++)
    {
      if (new_matrix[i] > probability)
        {
          index = i;
          probability = new_matrix[i];
        }
    }
  new_digit.probability = probability;
  new_digit.value = index;
  return new_digit;
}