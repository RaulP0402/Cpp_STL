#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <type_traits>
#include <concepts>
#include <initializer_list>
#include <iterator>

// template <typename Iter>
// concept Iterator = !std::is_integral_v<Iter>;

template <typename T>
class Vector 
{
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    void grow();
    void grow(size_t, const T& = T());

public:

    class Iterator 
    {
    private:
        T* pointer_;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using referece = T&;

        Iterator(T* pointer) : pointer_(pointer) {};
        T& operator*() const { return *pointer_; };
        T* operator->() const { return pointer_; };
        
        Iterator& operator++() { ++pointer_; return *this; };
        Iterator operator++(int) { Iterator tmp = *this; ++pointer_; return this; };

        Iterator& operator--() { --pointer_; return *this; };
        Iterator operator--(int) { Iterator tmp = *this; --pointer_; return tmp; };

        Iterator operator+(int n) const { return Iterator(pointer_ + n); };
        Iterator operator-(int n) const { return Iterator(pointer_ - n); };

        ptrdiff_t operator-(const Iterator& other) { return pointer_ - other.pointer_; };

        T& operator[](int n) const { return *(pointer_ + n); };

        bool operator==(const Iterator& other) const { return pointer_ == other.pointer_; };
        bool operator!=(const Iterator& other) const { return pointer_ != other.pointer_;  };
        bool operator>=(const Iterator& other) const { return pointer_ >= other.pointer_; };
        bool operator>(const Iterator& other) const { return pointer_ > other.pointer_; };
        bool operator<=(const Iterator& other) const { return pointer_ <= other.pointer_; };
        bool operator<(const Iterator& other) const { return pointer_ < other.pointer_; };
    };

    // ======================================
    // CONSTRUCTORS & DECONSTRUCTORS
    // ======================================
    Vector();                        // Empty
    Vector(size_t);                  // Default Fill
    Vector(size_t, const T&);        // Value Fill
    template <std::input_iterator InputIt>
    Vector(InputIt, InputIt);        // Range
    Vector(const Vector&);           // Copy
    Vector(Vector&&);                // Move
    Vector(std::initializer_list<T>); // Initalizer 
    ~Vector();

    // ITERATORS
    Iterator begin();
    const Iterator begin() const;
    Iterator end();
    const Iterator end() const;

    // CAPACITY
    size_t size() const;
    size_t capacity() const;
    size_t max_size() const;
    void resize(size_t, const T& = T());
    bool empty() const;
    void reserve(size_t);

    // INSERTION
    void push_back(const T&);
    void push_back(T&&);

    // ACCESS
    T& operator[](size_t);
    const T& operator[](const size_t) const;
    T& at(size_t);
    const T& at(size_t) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* data();
    const T* data() const;
};

#include "vector.tpp"

#endif
