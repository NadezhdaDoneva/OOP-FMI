#pragma once

#include <iostream>

template <typename T>
class PolymorphicPtr {
public:
    PolymorphicPtr() = default;
    PolymorphicPtr(const PolymorphicPtr<T>& other);
    PolymorphicPtr& operator= (const PolymorphicPtr<T>& other);

    PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept;
    PolymorphicPtr& operator= (PolymorphicPtr<T>&& other) noexcept;

    PolymorphicPtr(T* ptr);

    T* operator -> ();
    const T* operator -> () const;

    T& operator* ();
    const T& operator* () const;

    operator bool() const;
    void reset(T* data);

    T* get();
    const T* get() const;

    ~PolymorphicPtr();

private:
    T* data = nullptr;

    void copyFrom(const PolymorphicPtr<T>& other);
    void moveFrom(PolymorphicPtr<T>&& other) noexcept;
    void free();

};

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr<T>& other) {
    copyFrom(other);
}

template <typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator= (const PolymorphicPtr<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept {
    moveFrom(std::move(other));
}

template <typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>:: operator= (PolymorphicPtr<T>&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
PolymorphicPtr<T> ::PolymorphicPtr(T* ptr) : data(ptr) {}

template <typename T>
T* PolymorphicPtr<T>::operator -> () {
    return data;
}

template <typename T>
const T* PolymorphicPtr<T>::operator -> () const {
    return data;
}

template <typename T>
T& PolymorphicPtr<T>::operator* () {
    if (!data) {
        throw std::runtime_error("pointer in null");
    }

    return *data;
}

template <typename T>
const T& PolymorphicPtr<T>::operator* () const {
    if (!data) {
        throw std::runtime_error("pointer in null");
    }
    return *data;
}

template <typename T>
PolymorphicPtr<T> :: ~PolymorphicPtr() {
    free();
}

template <typename T>
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr<T>& other) {
    data = other.data->clone();
}
template <typename T>
void PolymorphicPtr<T>::moveFrom(PolymorphicPtr<T>&& other) noexcept {
    data = other.data;
    other.data = nullptr;
}

template <typename T>
void PolymorphicPtr<T>::free() {
    delete data;
}

template<class T>
PolymorphicPtr<T>::operator bool() const
{
    return data != nullptr;
}

template<class T>
void PolymorphicPtr<T>::reset(T* data)
{
    if (this->data != data) {
        free();
        this->data = data;
    }
}

template<class T>
T* PolymorphicPtr<T>::get()
{
    return data;
}

template<class T>
const T* PolymorphicPtr<T>::get() const
{
    return data;
}