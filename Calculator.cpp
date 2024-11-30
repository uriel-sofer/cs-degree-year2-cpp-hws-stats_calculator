#include "Calculator.h"
#include <sstream>


Calculator::Calculator(const int vecDim, const int maxCapacity) : observationsDict(maxCapacity),
                                                                        vecDim(vecDim), maxCapacity(maxCapacity), meanVector(vecDim)
{}


void Calculator::addObservation() {
    VectorDouble vector(vecDim);

    std::cout << "Enter observation name:" << std::endl;
    std::string observationName;
    std::cin >> observationName;

    std::cout << "Enter observation values:" << std::endl;
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
        std::cerr << "Invalid observation." << std::endl;
        return;
    }

    observationsDict.insert(observationName, vector);
}

void Calculator::printObservation() const {
    std::cout << "Enter observation name:" << std::endl;
    std::string observationName;
    std::cin >> observationName;

    const int search = observationsDict.contains(observationName);
    if (search == -1) {
        std::cerr << "Invalid or nonexistent observation." << std::endl;
        return;
    }
    observationsDict.printKeyValuePair(observationName);

}

void Calculator::calculateMeanVector()
{
    VectorDouble sumVector(vecDim);
    float* dimsSum = new float[vecDim](); // Init to 0

    for (int i = 0; i < observationsDict.getSize(); i++)
    {
        for (int j = 0; j < vecDim; j++)
        {
            dimsSum[j] += (float)(observationsDict[i]->value[j]);
        }
    }

    for (int i = 0; i < vecDim; i++)
    {
        sumVector.push_back(dimsSum[i] / observationsDict.getSize());
    }

    delete[] dimsSum;
    meanVector = sumVector;
}

void Calculator::calculateCovarianceMatrix()
{
    const int numObservations = observationsDict.getSize();
    float ** covarianceMatrix = new float *[vecDim];
    for (int i = 0; i < vecDim; ++i) {
        covarianceMatrix[i] = new float [vecDim]();
    }

    for (int i = 0; i < vecDim; ++i) {
        for (int j = 0; j < vecDim; ++j) {
            float sum = 0.0;

            for (int k = 0; k < numObservations; ++k) {
                const KeyValuePair* observation = observationsDict[k];
                const double* observationData = observation->value.getData();

                const float centered_i = (float)(observationData[i] - meanVector[i]);
                const float centered_j = (float)(observationData[j] - meanVector[j]);

                sum += centered_i * centered_j;
            }

            // Normalize
            covarianceMatrix[i][j] = numObservations > 1 ? sum / (numObservations - 1) : sum;
        }
    }

    // Print
    std::cout << "cov = [" << std::endl;
    for (int i = 0; i < vecDim; ++i) {
        for (int j = 0; j < vecDim; ++j) {
            std::cout << " " << covarianceMatrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "]";

    // Free
    for (int i = 0; i < vecDim; ++i) {
        delete[] covarianceMatrix[i];
    }
    delete[] covarianceMatrix;
}


void Calculator::expectedValueVector()
{
    if (isEmptyCalculator()) return;

    calculateMeanVector();
    std::cout << "mean = ";
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
        std::cerr << "Empty calculator." << std::endl;
        return true;
    }
    return false;
}
