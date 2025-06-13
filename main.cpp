#include "vector.h"
#include <iostream>
#include <cassert>

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
    std::cout << "\n";
    std::cout << "Testing Vector Implementation...\n";

    std::cout << "Vector Specifics After Initialization of 10 elements: \n";
    {
        Vector<T>v(10, fillValue);
        std::cout << "\tSize: " << v.size() << "\n";
        std::cout << "\tCapacity: " << v.capacity() << "\n";
        std::cout << "\tMax Size: " << v.max_size() << "\n";
    }

    std::cout << "Empty constructor: ";
    {
        Vector<T> v;
        assert(v.size() == 0);
        std::cout << "PASSED\n";
    }

    std::cout << "Fill constructor with unset values: ";
    {
        Vector<T> v(10);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i) {
            assert(v[i] == T());
        }
        std::cout << "PASSED\n";
    }

    std::cout << "Fill constructor with set values: ";
    {
        Vector<T>v(10, fillValue);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i) 
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";
    }

    std::cout << "Range Constructor: ";
    {
        Vector<T>other(10, fillValue);
        Vector<T>v(other);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";
    }

    std::cout << "Move Constructor: ";
    {
        Vector<T>v(Vector<T>(10, fillValue));
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";
    }

    std::cout << "Initializer List: ";
    {
        Vector<T>v = {fillValue, fillValue, fillValue, fillValue, fillValue};
        assert(v.size() == 5);
        for (size_t i = 0; i < 5; ++i)
            assert(v[i] == fillValue);
        std::cout<<"PASSED\n";
    }

    std::cout << "Resize Method: \n";
    {
        Vector<T>v(10, fillValue);

        std::cout << "\tResizing from 10 -> 5: ";
        v.resize(5);
        assert(v.size() == 5);
        for (size_t i = 0; i < 5; ++i)
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";

        std::cout << "\tResizing from 5 -> 10: ";
        v.resize(10);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";

        std::cout << "\tResizing from 10 -> 5 with val: ";
        v.resize(5, fillValue);
        assert(v.size() == 5);
        for (size_t i = 0; i < 5; ++i)
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";

        std::cout << "\tResizing from 5 -> 10 with val: ";
        v.resize(10, fillValue);
        assert(v.size() == 10);
        for (size_t i = 0; i < 10; ++i)
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";

        std::cout << "\tResizing from 10 -> 100: ";
        v.resize(100, fillValue);
        assert(v.size() == 100);
        for (size_t i = 0; i < 100; ++i)
            assert(v[i] == fillValue);
        std::cout << "PASSED\n";

    }

    std::cout << "Push back method: ";
    {
        Vector<T>v;
        for (size_t i = 0; i < 10; ++i) {
            v.push_back(fillValue);
            assert(v.size() == i + 1 && v[i] == T());
        }
        std::cout << "PASSED\n";
    }

    std::cout << "\n";
}
