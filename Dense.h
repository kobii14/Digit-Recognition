#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H
#include "Activation.h"

class Dense
{
 public:
  /// constructor to dense object that initializes a new layer with parameters
  /// \param w weight matrix
  /// \param bias bias matrix
  /// \param act_type RELO/SOFTMAX
  Dense(Matrix& w, Matrix& bias, ActivationType act_type): _act_type(act_type)
  {
    _w = w;
    _bias = bias;
  }
  // getters
  Matrix get_weights() const {return _w;};
  Matrix get_bias() const {return _bias;};
  Activation get_activation() const {return _act_type;};
  /// () operator that cannot change values and applies the layer on input
  /// \param matrix the matrix to activate the layer on
  /// \return output new matrix
  Matrix operator()(const Matrix& matrix) const;
 private:
  Matrix _w;
  Matrix _bias;
  Activation _act_type;
};
#endif //C___PROJECT_DENSE_H
