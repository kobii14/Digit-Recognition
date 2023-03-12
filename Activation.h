//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include <iostream>
#include "Matrix.h"
#define BAD_ACTION "Error: wrong action"
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};
class Activation
{
 public:
  // the constructor with parameter of action type
  Activation(ActivationType act_type)
  {
    if (act_type != RELU && act_type != SOFTMAX)
      {
        std::cerr << BAD_ACTION << std::endl;
        exit(EXIT_FAILURE);
      }
    _act_type = act_type;
  }
  // returns the activation type
  ActivationType get_activation_type() const{return _act_type;};
///  () operator that applies activation function on input
  Matrix operator()(const Matrix& matrix) const;
 private:
  ActivationType _act_type;
};

#endif //ACTIVATION_H
