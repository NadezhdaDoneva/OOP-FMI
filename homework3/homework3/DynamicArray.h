#pragma once
#include "PartialFunction.h"
class DynamicArray
{
private:
    PartialFunction** data = nullptr;
    size_t capacity = 0;
    size_t size = 0;


    //ok
    void copyFrom(const DynamicArray& other) {
        capacity = other.capacity;
        size = other.size;
        data = new PartialFunction* [other.capacity];
        for (size_t i; i < size; i++) {
            data[i] = other.data[i]->clone();
        }
    }

    //ok
    void moveFrom(DynamicArray&& other) {
        capacity = other.capacity;
        size = other.size;
        data = other.data;
        other.data = nullptr;
    }

    //ok
    void free() {
        for (size_t i = 0; i < capacity; i++) {
            delete data[i];
        }
        capacity = 0;
        size = 0;
    }

public:
    //ok
    DynamicArray(unsigned cap) {
        capacity = cap;
        data = new PartialFunction * [capacity];
        size = 0;
    }
    DynamicArray() : data(nullptr), capacity(0), size(0) {}

    //ok
    DynamicArray(const DynamicArray& other) {
        copyFrom(other);
    }
    DynamicArray(DynamicArray&& other) noexcept {
        moveFrom(std::move(other));
    }

    //ok
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    //ok
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }

    //ok
    ~DynamicArray()
    {
        free();
    }

    void add(const PartialFunction& value)
    {
        data[size++] = value.clone();
    }

    const PartialFunction* operator[](unsigned idx) const {
        return data[idx];
    }

    size_t get_size() const
    {
        return size;
    }


    bool isGivenFuncDefinedForSpecificNum(unsigned idx, int x) {
        if (idx > size) {
            return false;
        }
        return (*this)[idx]->isDefined(x);
    }
};