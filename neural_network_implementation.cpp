#include "network_dimensions_and_array_allocation.h"
#include "helper_functions.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <math.h>
#include <string>

// This file contains simple NN implementation
// Created:       05.05.2023
// Last modified: 05.05.2023

// Back-propagation algorithm choseb: stochastic gradient descent (SGD)
// Therefore weights are updated based on a single pair of inputs/expected outputs

int main(int argc, char *argv[]) {

// Iterations
int epochs = 10000;
std::cout << "Epochs: " << epochs << std::endl;

// Learning rate
const double lr = 0.1;
std::cout << "Learning rate: " << lr << std::endl;


// Training set:
static const int numTrainingSets = 4;
std::cout << "Number of training sets: " << numTrainingSets << std::endl;

double training_inputs[numTrainingSets][numInputs] = { {0.0,0.0},{1.0,0.0},{0.0,1.0},{1.0,1.0} };
double training_outputs[numTrainingSets][numOutputs] = { {0.0},{1.0},{1.0},{0.0} };
/*
std::cout << "Training input pairs:\n" << std::endl;
for (int i=0; i< sizeof(training_inputs); i++) { 
    std::string str = std::to_string(array_to_string(training_inputs[i], 2));
    std::cout << str << std::endl;
}
std::cout << "\n" << std::endl;
*/
/*
std::cout << "Training outputs:\n" << std::endl;
for (int i=0; i< sizeof(training_outputs); i++) {
    std::string str = std::to_string(training_outputs[i]);
    std::cout << str << std::endl;
}
std::cout << "\n" << std::endl;
*/

int trainingSetOrder[] = {0,1,2,3};

// Iterate through the entire training for a number of epochs
for (int n=0; n < epochs; n++) {
   
    // As per SGD, shuffle the order of the training set
    shuffle(trainingSetOrder,numTrainingSets);
    
    // Cycle through each of the training set elements
    for (int x=0; x<numTrainingSets; x++) {
    
        // Take single pair of training inputs
        int i = trainingSetOrder[x];
        
        // ========== Compute hidden layer activation with sigmoid ==========
        for (int j=0; j<numHiddenNodes; j++) {
          double activation=hiddenLayerBias[j];
          
            for (int k=0; k<numInputs; k++) {
              activation+=training_inputs[i][k]*hiddenWeights[k][j];
            }
            
          hiddenLayer[j] = sigmoid(activation);
          
        // ========== Compute output layer activation with sigmoid ========== 
        for (int j=0; j<numOutputs; j++) {
          double activation=outputLayerBias[j];
          for (int k=0; k<numHiddenNodes; k++) {
            activation+=hiddenLayer[k]*outputWeights[k][j];
          }
          outputLayer[j] = sigmoid(activation);
        }
        // ========== Calculating a small incremental change in the network ==========
        
        /* Idea is to move the network towards minimizing the error of the
        previouslycomputed output. Change in weights is calculated by:
        1. Calculating error wit MSE
        2. Multiplying derivative of the error by the derivative of the output
        at that node* -> dSigmoid from helper_functions.h */
        
        // Computing change in output weights
        double deltaOutput[numOutputs];
        for (int j=0; j<numOutputs; j++) {
            double dError = (training_outputs[i][j]-outputLayer[j]);
            deltaOutput[j] = dError*dSigmoid(outputLayer[j]);
        }
        
        /* Computing change in hidden weights, very similar, difference in how
        error is calculated. As it is the sum of the error across all output nodes.
        */
        
        double deltaHidden[numHiddenNodes];
            for (int j=0; j<numHiddenNodes; j++) {
                double dError = 0.0;
                for(int k=0; k<numOutputs; k++) {
                    dError+=deltaOutput[k]*outputWeights[j][k];
                }
            deltaHidden[j] = dError*dSigmoid(hiddenLayer[j]);
        }
        // Apply change in output weights
        for (int j=0; j<numOutputs; j++) {
          outputLayerBias[j] += deltaOutput[j]*lr;
            for (int k=0; k<numHiddenNodes; k++) {
              outputWeights[k][j]+=hiddenLayer[k]*deltaOutput[j]*lr;
            }
        }
        // Apply change in hidden weights
        for (int j=0; j<numHiddenNodes; j++) {
          hiddenLayerBias[j] += deltaHidden[j]*lr;
          for(int k=0; k<numInputs; k++) {
            hiddenWeights[k][j]+=training_inputs[i][k]*deltaHidden[j]*lr;
          }
        }
     
       }        
        
    
    }
}
}
