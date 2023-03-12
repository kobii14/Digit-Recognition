//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H
#include "Matrix.h"
#include "Digit.h"
#include "Dense.h"

#define MLP_SIZE 4
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3


//
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork
{
 public:
  /// accept 2 arrays for weights and biases and construct the network with
  /// 4 layers
  /// \param weights weights for functions
  /// \param biases biases for functions
  MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]):
  layer_1(weights[ZERO], biases[ZERO], RELU),
  layer_2(weights[ONE], biases[ONE], RELU),
  layer_3(weights[TWO], biases[TWO], RELU),
  layer_4(weights[THREE], biases[THREE], SOFTMAX)
  {
  }
   digit operator()(const Matrix& matrix) const;
 private:
  Dense layer_1;
  Dense layer_2;
  Dense layer_3;
  Dense layer_4;
};

#endif // MLPNETWORK_H
