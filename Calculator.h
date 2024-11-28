#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Dict.h"

/**
 * This class stores observations in a dict like structure
 * It should have all the methods: 1-4 and more utility methods
 */
class Calculator {
    private:
    Dict observationsDict;
    int vecDim;
    int maxCapacity;

    VectorDouble meanVector;
    void calculateMeanVector(); // Calculates the Mean Vector
    void calculateCovarianceMatrix(); // Calculates the Covariance Matrix
    bool isEmptyCalculator() const; // Checks if the Calculator is empty and prints an error message if it is.

   public:
    Calculator(int vecDim, int maxCapacity);

    /**
     * Adds new observation (KeyValuePair of name and vector) to the calculator database
     * Adds the observation only of the given vector is within the dimensions
     * prompts for name and data, NOT for dimensions.
     */
    void addObservation();

    /**
     * Prompts for observation name and prints it
     */
    void printObservation() const;

    /**
     * Prints the mean value vector using the calculateExpectedValues() method
     */
    void expectedValueVector();

    /**
     * Prints the Covariance Matrix
     */
    void printCovarianceMatrix();
};



#endif //CALCULATOR_H
