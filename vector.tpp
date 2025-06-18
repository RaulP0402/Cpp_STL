#include "vector.h"
#include <utility>
#include <new>
#include <iostream>
#include <stdexcept>


// ======================================
// CONSTRUCTORS & DECONSTRUCTORS
// ======================================

// Empty Container Constructor
template <typename T>
Vector<T>::Vector() 
    : data_(nullptr)
    , size_(0)
    , capacity_(0) 
{}

// Fill Constructor to just size
template <typename T>
Vector<T>::Vector(size_t n)
    : data_(static_cast<T*>(::operator new(sizeof(T) * n)))
    , size_(n)
    , capacity_(n) 
{}

// Fill Constructor with values
template <typename T>
Vector<T>::Vector(const size_t n, const T& value)
    : data_(static_cast<T*>(::operator new(sizeof(T) * n)))
    , size_(n)
    , capacity_(n) 
{
    for (size_t i = 0; i < n; ++i)
        new(data_ + i) T(value);
}

// Range Constructor
template <typename T>
template <std::input_iterator InputIt>
Vector<T>::Vector(InputIt begin, InputIt end)
    : data_(nullptr)
    , size_(0)
    , capacity_(0)
{
    size_t count = 0;
    for (InputIt i = begin; i != end; ++i) 
        count++;
    
    data_ = static_cast<T*>(::operator new(sizeof(T) * count));
    capacity_ = count;

    for (size_t i = 0; i < count; ++i, ++begin) {
        new (data_ + i) T(*begin);
    }

    size_ = count;
}

// Copy Constructor
template <typename T>
Vector<T>::Vector(const Vector& other) 
    : size_(other.size())
    , capacity_(other.size())
{
    data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));

    for (size_t i = 0; i < size_; ++i)
        new(data_ + i) T(other[i]);
}

// Move Constructor
template <typename T>
Vector<T>::Vector(Vector&& other)
    :size_(other.size())
    , capacity_(other.size())
{
    data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));

    for (size_t i = 0; i < size_; ++i)
        new(data_ + i) T(std::move(other[i]));
}

// Initilaizer List
template <typename T>
Vector<T>::Vector(std::initializer_list<T> ilist)
    : data_(nullptr)
    , size_(0)
    , capacity_(ilist.size())
{   
    data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));

    for (const T& t: ilist) {
        new(data_ + size_) T(t);
        ++size_;
    }
}

// Deconstructor
template <typename T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < size_; ++i) 
        data_[i].~T();

    ::operator delete(data_);
}

// ======================================
// ITERATOR METHODS
// ======================================

template <typename T>
Vector<T>::Iterator Vector<T>::begin() 
{
    return Vector<T>::Iterator(data_);
}

template <typename T>
const Vector<T>::Iterator Vector<T>::begin() const 
{
    return Vector<T>::Iterator(data_);
}

template <typename T>
Vector<T>::Iterator Vector<T>::end()
{
    return Vector<T>::Iterator(data_ + size_);
}

template <typename T>
const Vector<T>::Iterator Vector<T>::end() const 
{
    return Vector<T>::Iterator(data_ + size_);
}

// ======================================
// CAPACITY METHODS
// ======================================

// Size
template <typename T>
size_t Vector<T>::size() const {
    return size_;
}

// Capacity
template <typename T>
size_t Vector<T>::capacity() const {
    return capacity_;
}

// Max size
template <typename T>
size_t Vector<T>::max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

// Resize
template <typename T>
void Vector<T>::resize(size_t n, const T& fillValue) {
    if (n > capacity_) {
        grow(n, fillValue);
        return;
    }

    if (n <= size_) {
        for (size_t i = n; i < size_; ++i)
            data_[i].~T();
        size_ = n;
    } else {
        for (size_t i = size_; i < n; ++i)
            new (data_ + i) T(fillValue);
        size_ = n;
    }
}

// Empty
template <typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

// Reserve
template <typename T>
void Vector<T>::reserve(size_t n) {
    if (n > capacity_)
        grow(n);
}

// ======================================
// ACCESS METHODS
// ======================================

// Elemenent Access / Indexing
template <typename T>
T& Vector<T>::operator[](size_t index) {
    return *(data_ + index);
}

// Constant element access
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    return *(data_ + index);
}

// At access
template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_)
        throw std::out_of_range("Vector index out of range");
    return *(data_ + index);
}

template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size_)
        throw std::out_of_range("Vector index out of range");
    return *(data_ + index);
}


// Front
template <typename T>
T& Vector<T>::front() 
{
    return *(data_);
}

template <typename T>
const T& Vector<T>::front() const 
{
    return *(data_);
}

// Back
template <typename T>
T& Vector<T>::back() 
{
    return *(data_ + size_ - 1);
}

template <typename T>
const T& Vector<T>::back() const 
{
    return *(data_ + size_ - 1);
}

// Data
template <typename T>
T* Vector<T>::data() 
{
    return data_;
}

template <typename T>
const T* Vector<T>::data() const 
{
    return data_;
}

// ======================================
// MODIFIER METHODS
// ======================================

// Push back
template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_)
        grow();
    
    new (data_ + size_) T(value);
    size_++;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ == capacity_)
        grow();
    
    new (data_ + size_ ) T(std::move(value));
    size_++;
}

// ======================================
// HELPER METHODS
// ======================================

// Grow 
template <typename T>
void Vector<T>::grow() {
    size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
    T* newData_ = static_cast<T*>(::operator new(sizeof(T) * newCapacity));
    
    // Move old elements to new data
    for (size_t i = 0; i < size_; ++i) {
        new (newData_ + i) T(std::move(data_[i]));
        data_[i].~T();
    }

    ::operator delete(data_);
    data_ = newData_;
    capacity_ = newCapacity;
}

// Grow to size n
template <typename T>
void Vector<T>::grow(size_t n, const T& fillValue) {
    size_t newCapacity = n;
    T* newData_ = static_cast<T*>(::operator new(sizeof(T) * newCapacity));
    
    // Move old elements to new data
    for (size_t i = 0; i < size_; ++i) {
        new (newData_ + i) T(std::move(data_[i]));
        data_[i].~T();
    }

    // Initialize rest of elements 
    for (size_t i = size_; i < n; ++i)
        new (newData_ + i) T(fillValue);

    ::operator delete(data_);
    data_ = newData_;
    capacity_ = newCapacity;
    size_ = n;
}