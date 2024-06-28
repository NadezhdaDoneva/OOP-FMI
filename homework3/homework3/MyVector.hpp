#pragma once

#include <iostream>

template <class T>
class MyVector {
public:
    MyVector();
    MyVector(const MyVector<T>& other);
    MyVector& operator=(const MyVector<T>& other);

    MyVector(MyVector<T>&& other) noexcept;
    MyVector& operator=(MyVector<T>&& other) noexcept;

    ~MyVector();

    size_t getSize() const;
    size_t getCapacity() const;

    void pushBack(const T& element);
    void pushBack(T&& element);

    void popBack();

    void insert(const T& element, size_t index);
    void insert(T&& element, size_t index);

    void erase(size_t index);

    void clear();

    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    bool isEmpty() const;


private:
    static const size_t INITIAL_CAP = 8;
    static const size_t RESIZE_COEF = 2;

    T* data = nullptr;
    size_t size = 0;
    size_t capacity = INITIAL_CAP;

    void resize(size_t newCap);

    explicit MyVector(size_t capacity);

    void free();
    void moveFrom(MyVector<T>&& other) noexcept;
    void copyFrom(const MyVector<T>& other);

};


template <class T>
MyVector<T> ::MyVector() : MyVector(INITIAL_CAP) {}

template <class T>
MyVector<T>::MyVector(size_t capacity) : capacity(capacity) {
    data = new T[capacity];
    size = 0;
}

template <class T>
MyVector<T>::MyVector(const MyVector<T>& other) {
    copyFrom(other);
}

template <class T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept {
    moveFrom(std::move(other));
}

template <class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <class T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <class T>
MyVector<T> :: ~MyVector() {
    free();
}


template <class T>
void MyVector<T>::resize(size_t newCap) {
    capacity = newCap;

    T* temp = new T[capacity];

    for (size_t i = 0; i < size; i++) {
        temp[i] = std::move(data[i]);
    }

    delete[] data;
    data = temp;
}

template <class T>
size_t MyVector<T> ::getCapacity() const {
    return capacity;
}

template <class T>
size_t MyVector<T>::getSize() const {
    return size;
}

template <class T>
void MyVector<T> ::free() {
    delete[] data;
    data = nullptr;
}

template <class T>
void MyVector<T>::copyFrom(const MyVector<T>& other) {

    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];

    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }

}

template <class T>
void MyVector<T>::moveFrom(MyVector<T>&& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    data = other.data;

    other.data = nullptr;
}

template <class T>
void MyVector<T>::pushBack(T&& element) {
    if (size == capacity) {
        resize(capacity * RESIZE_COEF);
    }

    data[size++] = std::move(element);
}

template <class T>
void MyVector<T>::pushBack(const T& element) {
    if (size == capacity) {
        resize(capacity * RESIZE_COEF);
    }

    data[size++] = (element);
}

template <class T>
void MyVector<T>::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("unable to remove element from empty vector");
    }

    if (size * RESIZE_COEF * RESIZE_COEF == capacity) {
        resize(capacity / RESIZE_COEF);
    }

    size--;
}

template <class T>
void MyVector<T>::insert(T&& element, size_t index) {
    if (index >= size) {
        throw std::out_of_range("index out of range");
    }

    if (size == capacity) {
        resize(capacity * RESIZE_COEF);
    }

    for (int i = size; i > index; i--) {
        data[i] = std::move(data[i]);
    }

    data[index] = std::move(element);
    size++;
}

template <class T>
void MyVector<T>::insert(const T& element, size_t index) {
    if (index >= size) {
        throw std::out_of_range("index out of range");
    }

    if (size == capacity) {
        resize(capacity * RESIZE_COEF);
    }

    for (int i = size; i > index; i--) {
        data[i] = std::move(data[i]);
    }

    data[index] = (element);
    size++;
}

template <class T>
void MyVector<T>::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("index out of range");
    }

    if (size * RESIZE_COEF * RESIZE_COEF == capacity) {
        resize(capacity / RESIZE_COEF);
    }

    size--;

    for (size_t i = index; i < size; i++) {
        data[i] = std::move(data[i + 1]);
    }
}

template <class T>
void MyVector<T>::clear() {
    free();
    size = 0;
    capacity = INITIAL_CAP;
    data = new T[capacity];
}

template <class T>
const T& MyVector<T>::operator[](size_t index) const {
    return data[index];
}

template <class T>
T& MyVector<T>::operator[](size_t index) {
    return data[index];
}

template <class T>
bool MyVector<T> ::isEmpty() const {
    return size == 0;
}