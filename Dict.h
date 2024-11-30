#ifndef DICT_H
#define DICT_H

#include <string>
#include <iostream>
#include "VectorDouble.h"


class Dict;
class Calculator;

/**
 * My version of a tuple, to be used in the Dict class
 */
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

    /**
     * @param key the identifier (Observation name in our case)
     * @param value the value (VectorDouble in our case)
     */
    void insert(const std::string& key, const VectorDouble& value);

    /**
     * @param pair An observation "tuple" to be inserted
     */
    void insert(const KeyValuePair& pair);

    /**
     *
     * @param key Observation name
     * @return pointer to the observation's vector
     */
    VectorDouble* get(const std::string& key) const;

    /**
     * 
     * @param key Observation name
     * @return the observation's index in the dict or -1 if not in dict
     */
    int contains(const std::string& key) const;

    /**
     * 
     * @param key Observation name to be printed
     */
    void printKeyValuePair(const std::string& key) const;

    /**
     * Prints the whole dict
     */
    void print() const;

    /**
     * 
     * @return How many elements are currently in the dict
     */
    int getSize() const;

    /**
     * 
     * @return The total current capacity
     */
    int getCapacity() const;

    friend Calculator;
};

#endif // DICT_H
