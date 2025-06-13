#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <type_traits>
#include <concepts>
#include <initializer_list>

template <typename Iter>
concept Iterator = !std::is_integral_v<Iter>;

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    void grow();
    void grow(size_t, const T&);

public:
    // CONSTRUCTORS & DESTRUCToRS
    Vector();                        // Empty
    Vector(size_t);                  // Default Fill
    Vector(size_t, const T&);        // Value Fill
    template <Iterator InputIt>
    Vector(InputIt, InputIt);        // Range
    Vector(const Vector&);           // Copy
    Vector(Vector&&);                // Move
    Vector(std::initializer_list<T>); // Initalizer 
    ~Vector();

    // CAPACITY
    size_t size() const;
    size_t capacity() const;
    size_t max_size() const;
    void resize(size_t, const T& = T());

    void push_back(const T&);
    void push_back(T&&);


    T& operator[](size_t);
    T& operator[](const size_t) const;
};

#include "vector.tpp"

#endif
