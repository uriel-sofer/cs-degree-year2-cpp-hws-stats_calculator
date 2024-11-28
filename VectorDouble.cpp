#include "VectorDouble.h"


// ----------------- VectorDouble Implementation -----------------

VectorDouble::VectorDouble(const int dim) : size(0), dim(dim)
{
    data = new double[dim];
    for (int i = 0; i < dim; i++)
    {
        data[i] = 0.0;
    }
}


VectorDouble::~VectorDouble()
{
    delete[] data;
}


VectorDouble::VectorDouble(const VectorDouble& other) : size(other.size), dim(other.dim)
{
    data = new double[dim];
    for (int i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

bool VectorDouble::resize(int newCapacity)
{
    double* newData = new double[newCapacity];
    for (int i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }
    for (int i = size; i < newCapacity; i++)
    {
        newData[i] = 0.0;
    }

    delete[] data;
    data = newData;
    dim = newCapacity;
    return true;
}


VectorDouble& VectorDouble::operator=(const VectorDouble& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] data;
    size = other.size;
    dim = other.dim;
    data = new double[dim];
    for (int i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
    return *this;
}

void VectorDouble::push_back(const double& newElement)
{
    if (isFull())
    {
        std::cerr << "VectorDouble::VectorDouble::push_back() is full!" << std::endl;
        return;
    }
    data[size++] = newElement;
}


void VectorDouble::pop_back()
{
    if (size == 0)
    {
        std::cerr << "Cannot pop_back from an empty vector" << std::endl;
    }
    --size;
}

double& VectorDouble::operator[](int index) {
    if (index >= dim) {
        throw std::out_of_range("Index out of range.");
    }

    // Update size if accessing beyond current size
    if (index >= size) {
        size = index + 1;
    }

    return data[index];
}


const double& VectorDouble::operator[](const int index) const
{
    if (index >= size)
    {
        std::cerr << "Index out of range" << std::endl;
    }
    return data[index];
}

int VectorDouble::getSize() const
{
    return size;
}

int VectorDouble::getDim() const
{
    return dim;
}

const double* VectorDouble::getData() const
{
    return data;
}

bool VectorDouble::isEmpty() const
{
    return size == 0;
}

bool VectorDouble::isFull() const
{
    return size >= dim;
}

void VectorDouble::print() const
{
    std::cout << "[ ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << data[i] << " ";
    }
    for (int i = size; i < dim; ++i)
    {
        std::cout << "0 ";
    }
    std::cout << "]" << std::endl;
}

double VectorDouble::sum() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum;
}

