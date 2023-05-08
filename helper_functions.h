#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <list>
#include <cstdlib>
#include <math.h>
#include <string>

// This file contains generic helper functions
// Created:       05.05.2023
// Last modified: 05.05.2023

// Activation function
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

// Derivative of activation function
double dSigmoid(double x) {
    return x * (1 - x);
}

// Init all weights and biases between 0.0 and 1.0
double init_weight() {
    return ((double)rand())/((double)RAND_MAX);
}

/* Array of indexes is shuffled for every epoch in order to select a random pair,
while making sure that all the inputs are used per epoch*/
void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

std::string array_to_string(double* arr, int size) {
    std::string result = "{";
    for (int i = 0; i < size; i++) {
        result += std::to_string(arr[i]);
        if (i < size - 1) {
            result += ", ";
        }
    }
    result += "}";
    return result;
}


#endif // HELPER_FUNCTIONS_H
