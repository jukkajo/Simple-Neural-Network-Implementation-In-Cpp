#ifndef NETWORK_DIMENSIONS_AND_ARRAY_ALLOCATION_H
#define NETWORK_DIMENSIONS_AND_ARRAY_ALLOCATION_H

/* This file contains definitions for the dimensions of the network
   and it allocates the arrays for the layers, biases and weights 
*/
// Created:       05.05.2023
// Last modified: 05.05.2023

static const int numInputs = 2;
static const int numHiddenNodes = 2;
static const int numOutputs = 1;
double hiddenLayer[numHiddenNodes];
double outputLayer[numOutputs];
double hiddenLayerBias[numHiddenNodes];
double outputLayerBias[numOutputs];
double hiddenWeights[numInputs][numHiddenNodes];
double outputWeights[numHiddenNodes][numOutputs];

#endif // NETWORK_DIMENSIONS_AND_ARRAY_ALLOCATION_H
