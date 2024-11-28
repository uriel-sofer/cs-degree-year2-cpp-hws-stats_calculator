#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class VectorDouble {
private:
      double* data;
      int size;
      int dim;
      bool resize(int newCapacity);

public:
     explicit  VectorDouble(int dim);
     ~VectorDouble();

     VectorDouble(const VectorDouble& other);
     VectorDouble& operator=(const VectorDouble& other);

     void push_back(const double& newElement);
     void pop_back();
     double& operator[](int index);
     const double& operator[](int index) const;

     int getSize() const;
     int getDim() const;
     bool isEmpty() const;
     bool isFull() const;
     const double* getData() const;
     double sum() const;

     void print() const;
};

#endif // VECTOR_H
