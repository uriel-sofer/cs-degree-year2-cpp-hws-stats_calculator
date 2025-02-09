#include <iostream>

#include "Calculator.h"
#include "Dict.h"
#include "VectorDouble.h"

void main_menu();

int main(int argc, char* argv[])
{
    if (argc != 3) // Program name and two numbers
    {
        std::cerr << "Invalid arguments <int> <int>" << std::endl;
        return -1;
    }

    const int minDims = std::stoi(argv[1]);
    const int maxCapacity = std::stoi(argv[2]);

    if (maxCapacity <= 0 or minDims <= 0) {
        std::cerr << "Invalid arguments <int> <int>" << std::endl;
        return -1;
    }


    Calculator calc(minDims, maxCapacity);

    bool exit_flag = false;
    main_menu();
    while (not exit_flag)
    {
        // main_menu() here would be a better approach imo
        int choice;
        std::cin >> choice;

        switch (choice)
        {
            // New observation
            case 1:
                calc.addObservation();
                break;

            // Print observation
            case 2:
                calc.printObservation();
                break;

            // Calculate and print the Mean Vector
            case 3:
                calc.expectedValueVector();
                break;

            // Calculate and print the Covariance Matrix
            case 4:
                calc.printCovarianceMatrix();
                break;

            case 5:
                exit_flag = true;
                break;

        default:
                std::cerr << "Invalid option." << std::endl;
        }
    }

    return 0;
}

void main_menu()
{
    std::cout << "[1] New observation\n" << "[2] Print observation\n";
    std::cout << "[3] Expected value vector\n"<< "[4] Covariance matrix\n"<< "[5] Exit\n";
}