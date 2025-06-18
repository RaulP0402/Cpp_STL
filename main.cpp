#include "vector.h"
#include <iostream>
#include <cassert>

using std::cout;

template <typename T>
void printElements(Vector<T>&);
template <typename T>
void testVector(const T& fillValue = T());

int main() {
    int n = -1;
    while (n != 0) {    
        std::cout << "Please select the data structure you would like to test: \n";
        std::cout << "1. All\n";
        std::cout << "2. Vector\n";
        std::cout << "Enter 0 to exit.\n";
        std::cout << "> ";
        std::cin >> n;

        switch (n) {
            case (1):
                testVector<int>();
                break;
            case (2):
                testVector<int>();
                break;
            default:
                break;
        }
    }

    return 0;
}

template <typename T>
void testVector(const T& fillValue) {
    cout << "\n";
    cout << "TESTING VECTOR: ";

    {
        Vector<T>v(10, fillValue);
        assert(
            v.size() == 10 && \
            v.capacity() == 10
        );
    }

    // EMPTY CONSTRUCTOR 
    {
        Vector<T> v;
        assert(v.size() == 0);
    }

    // FILL CONSTRUCTOR WITH DEFAULT VALUE
    {
        Vector<T> v(10);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i) {
            assert(v[i] == T());
        }
    }

    // FILL CONSTRUCTOR WITH FILLVALUE
    {
        Vector<T>v(10, fillValue);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i) 
            assert(v[i] == fillValue);
    }

    // RANGE CONSTRUCTOR
    {
        Vector<T>other(10, fillValue);
        Vector<T>v(other.begin(), other.end());
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);
    }

    // MOVE CONSTRUCTOR
    {
        Vector<T>v(Vector<T>(10, fillValue));
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);
    }

    // LIST INTIALIZED CONSTRUCTOR
    {
        Vector<T>v = {fillValue, fillValue, fillValue, fillValue, fillValue};
        assert(v.size() == 5);
        for (size_t i = 0; i < 5; ++i)
            assert(v[i] == fillValue);
    }

    // RESIZE METHOD
    {
        Vector<T>v(10, fillValue);

        // 10 -> 5
        v.resize(5);
        assert(v.size() == 5);
        for (size_t i = 0; i < 5; ++i)
            assert(v[i] == fillValue);

        // 5 -> 10
        v.resize(10);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);

        // 10 -> 5 WITH FILLVALUE
        v.resize(5, fillValue);
        assert(v.size() == 5);
        for (size_t i = 0; i < 5; ++i)
            assert(v[i] == fillValue);

        // 5 -> 10 WITH FILLVALUE
        v.resize(10, fillValue);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);

        // 5 -> 100 WITH FILLVALUE
        v.resize(100, fillValue);
        assert(v.size() == 100);
        for (size_t i = 0; i < 100; ++i)
            assert(v[i] == fillValue);

    }

    // EMPTY()
    {
        Vector<T>v;
        assert(v.empty() == true);
        v.push_back(fillValue);
        assert(v.empty() != true);
    }

    // RESERVE()
    {
        Vector<T>v(10);
        v.reserve(1000);
        assert(v.capacity() == 1000);
    }

    // PUSH_BACK()
    {
        Vector<T>v;
        for (size_t i = 0; i < 10; ++i) {
            v.push_back(fillValue);
            assert(v.size() == i + 1 && v[i] == T());
        }
    }

    // ARR[i] AND AT()
    {
        Vector<T>v(10, fillValue);
        assert(v[9] == fillValue);
        v[9] = fillValue;
        assert(v.at(9) == fillValue);
        v.at(9) = fillValue;

        const Vector<T>constV(10, fillValue);
        assert(constV[9] == fillValue);
        assert(constV.at(9) == fillValue);
        
    }

    // FRONT() & BACK()
    {
        Vector<int> intVector;
        for (int i = 0; i < 100; ++i)
            intVector.push_back(i);
        assert(intVector.front() == 0);
        cout << "Back element is : " << intVector.back() << "\n";
        assert(intVector.back() == 99);
    }

    // DATA()
    {
        Vector<T> v(10, fillValue);
        const Vector<T> constV(10, fillValue);
        T* data = v.data();
        const T* constData = constV.data();
        for (size_t i = 0; i < 10; ++i)
        {
            assert(*(data + i) == fillValue && \
                    *(constData + i) == fillValue);
        }
    }

    std::cout << "PASSED\n\n";;
}
