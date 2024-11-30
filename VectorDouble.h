#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

/**
 * Class to hold a vector of doubles, instead of using an array
 * Can access internal data via getData() or via []
 */
class VectorDouble {
private:
      double* data;
      int size;
      int dim;
      bool resize(int newCapacity);

public:
      /**
       *  Init a Vector double
       * @param dim the vector's dimension
       */
      explicit  VectorDouble(int dim);
     ~VectorDouble();

     VectorDouble(const VectorDouble& other);
     VectorDouble& operator=(const VectorDouble& other);

      /**
       * Inserts a new element at the end
       * @param newElement nre element to be inserted
       */
      void push_back(const double& newElement);

      /**
       * returns a non const element reference
       * @param index index in the vector
       * @return reference to element at index in the vector
       */
      double& operator[](int index);

      /**
       * returns a const element reference
       * @param index index in the vector
       * @return const reference to the element at index, the element is safe and cannot be modified
       */
      const double& operator[](int index) const;

     int getSize() const;
     int getDim() const;
     bool isEmpty() const;
     bool isFull() const;
      /**
       * 
       * @return a pointer to the first element in data array
       */
      const double* getData() const;

      /**
       * 
       * @return the sum of the elements in the vector
       */
      double sum() const;


      /**
       * Prints the vector in the desired format
       */
      void print() const;
};

#endif // VECTOR_H
