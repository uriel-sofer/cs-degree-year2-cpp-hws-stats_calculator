#include "Dict.h"

Dict::Dict(const int MAX_SIZE) : size(0), capacity(8), MAX_SIZE(MAX_SIZE)
{
    data = new KeyValuePair*[capacity];
    for (int i = 0; i < capacity; i++)
    {
        data[i] = nullptr;
    }
}

Dict::~Dict()
{
    for (int i = 0; i < capacity; i++)
    {
        delete data[i];
    }
    delete[] data;
}

void Dict::resize()
{
    if (capacity >= MAX_SIZE) {
        std::cerr << "Error: Cannot resize. Capacity has reached the maximum limit: " << MAX_SIZE << std::endl;
        return;
    }

    int newCapacity = std::min(2 * capacity, MAX_SIZE); // Ensure it doesn't exceed MAX_SIZE
    KeyValuePair** newData = new KeyValuePair*[newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newData[i] = nullptr;
    }

    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

KeyValuePair *Dict::operator[](int index) const {
    if (index >= size) {
        std::cerr << "Index out of bounds" << index << std::endl;
        return nullptr;
    }
    return data[index];
}

void Dict::insert(const std::string& key, const VectorDouble& value)
{

    for (int i = 0; i < size; i++)
    {
        if (data[i]->key == key)
        {
            data[i]->value = value;
            return;
        }
    }

    if (size == capacity)
    {
        resize();
    }

    data[size++] = new KeyValuePair(key, value);
}

void Dict::insert(const KeyValuePair &pair) {
    insert(pair.key, pair.value);
}

VectorDouble* Dict::get(const std::string& key) const {
    const int search = contains(key);
    if (search != -1)
        return &data[search]->value;
    std::cerr << "Key " << key << " not found" << std::endl;
    return nullptr;
}

int Dict::contains(const std::string& key) const
{
    for (int i = 0; i < size; i++)
    {
        if (data[i]->key == key)
            return int(i);
    }
    return -1;
}

void Dict::printKeyValuePair(const std::string &key) const {
    int search = contains(key);
    if (search != -1) {
        std::cout << data[search]->key << " = ";
        data[search]->value.print();
    }
}

void Dict::print() const
{
    for (int i = 0; i < size; i++)
    {
        std::cout << data[i]->key << " = ";
        data[i]->value.print();
    }
}

int Dict::getSize() const {
    return size;
}

int Dict::getCapacity() const {
    return capacity;
}

