#ifndef DICT_H
#define DICT_H

#include <string>
#include <iostream>
#include <utility>
#include "VectorDouble.h"
class Dict;
class Calculator;

class KeyValuePair {
private:
    std::string key;
    VectorDouble value;

public:
    KeyValuePair(std::string  key, const VectorDouble& value)
    : key(std::move(key)), value(value) {}

    void print() const
    {
        std::cout << "(" << key << ": ";
        value.print();
        std::cout << ")";
    }

    friend Dict;
    friend Calculator;
};


class Dict {
private:
    KeyValuePair** data; // Array of pointers, for easier memory management
    int size;         // Current number of key-value pairs
    int capacity;     // Current capacity of the array, current max places
    const int MAX_SIZE;

    void resize();       // Resize when size = capacity and capacity < MAX_CAPACITY

protected:
    KeyValuePair* operator[](int index) const;

public:
     explicit Dict(int MAX_SIZE);
    ~Dict();

    void insert(const std::string& key, const VectorDouble& value);
    void insert(const KeyValuePair& pair);
    VectorDouble* get(const std::string& key) const;
    int contains(const std::string& key) const;
    void printKeyValuePair(const std::string& key) const;
    void print() const;

    int getSize() const;
    int getCapacity() const;

    friend Calculator;
};

#endif // DICT_H
