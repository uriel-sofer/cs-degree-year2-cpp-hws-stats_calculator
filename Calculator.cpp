#include "Calculator.h"
#include <math.h>
#include <sstream>


Calculator::Calculator(const int vecDim, const int maxCapacity) : observationsDict(maxCapacity),
                                                                        vecDim(vecDim), maxCapacity(maxCapacity), meanVector(vecDim)
{}


void Calculator::addObservation() {
    VectorDouble vector(vecDim);

    std::cout << "Enter observation name: ";
    std::string observationName;
    std::cin >> observationName;

    std::cout << "Enter " << vecDim << " values separated by spaces: ";
    std::string observationValues;

    // Clear newline from the previous input
    std::cin.ignore();
    std::getline(std::cin, observationValues);

    std::stringstream ss(observationValues);
    double value;
    int valueCount = 0;
    while (ss >> value) {
        vector.push_back(value);
        valueCount++;
        // Skip the delimiter
        if (ss.peek() == ' ') {
            ss.ignore();
        }
    }

    if (valueCount != vecDim)
    {
        std::cerr << "Error: You must provide  " << vecDim << " values." << std::endl;
        return;
    }

    observationsDict.insert(observationName, vector);
    std::cout << "Observation \"" << observationName << "\" added successfully." << std::endl;
}

void Calculator::printObservation() const {
    std::cout << "Enter observation name for printing: ";
    std::string observationName;
    std::cin >> observationName;

    const int search = observationsDict.contains(observationName);
    if (search == -1) {
        std::cerr << "Invalid or nonexistent observation " << std::endl;
        return;
    }
    observationsDict.printKeyValuePair(observationName);

}

void Calculator::calculateMeanVector()
{

    VectorDouble sumVector(vecDim);
    double* dimsSum = new double[vecDim](); // Init to 0

    for (int i = 0; i < observationsDict.getSize(); i++)
    {
        for (int j = 0; j < vecDim; j++)
        {
            dimsSum[j] += observationsDict[i]->value[j];
        }
    }

    for (int i = 0; i < vecDim; i++)
    {
        sumVector.push_back(dimsSum[i] / observationsDict.getSize());
    }

    delete[] dimsSum;
    meanVector = sumVector;

}

void Calculator::calculateCovarianceMatrix() {
    if (observationsDict.getSize() == 0) {
        std::cerr << "Error: No observations to compute the covariance matrix." << std::endl;
        return;
    }

    const int numObservations = observationsDict.getSize();
    float** covarianceMatrix = new float*[vecDim];
    for (int i = 0; i < vecDim; ++i) {
        covarianceMatrix[i] = new float[vecDim]();
    }

    for (int i = 0; i < vecDim; ++i) {
        for (int j = 0; j < vecDim; ++j) {
            double sum = 0.0;

            for (int k = 0; k < numObservations; ++k) {
                const KeyValuePair* observation = observationsDict[k];
                const double* observationData = observation->value.getData();

                const double centered_i = observationData[i] - meanVector[i];
                const double centered_j = observationData[j] - meanVector[j];

                sum += centered_i * centered_j;
            }

            // Normalize
            covarianceMatrix[i][j] = numObservations > 1 ? sum / numObservations : sum;
        }
    }

    // Step 2: Print the covariance matrix
    std::cout << "cov = [" << std::endl;
    for (int i = 0; i < vecDim; ++i) {
        for (int j = 0; j < vecDim; ++j) {
            std::cout << covarianceMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;

    // Step 3: Free dynamically allocated memory
    for (int i = 0; i < vecDim; ++i) {
        delete[] covarianceMatrix[i];
    }
    delete[] covarianceMatrix;
}


void Calculator::expectedValueVector()
{
    if (isEmptyCalculator()) return;

    std::cout << "mean = ";
    calculateMeanVector();
    meanVector.print();
}

void Calculator::printCovarianceMatrix()
{
    if (isEmptyCalculator()) return;

    calculateCovarianceMatrix();
}


bool Calculator::isEmptyCalculator() const
{
    if (observationsDict.getSize() == 0)
    {
        std::cerr << "Empty calculator";
        return true;
    }
    return false;
}
