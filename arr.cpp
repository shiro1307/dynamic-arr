#include <iostream>
#include <utility>
#include <stdexcept>
using namespace std;

template <typename T>
class Arr {
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        if (newCapacity < size)
            newCapacity = size;

        T* newdata = new T[newCapacity];

        try {
            for (size_t i = 0; i < size; i++)
                newdata[i] = std::move(data[i]);
        } catch (...) {
            delete[] newdata;
            throw;
        }

        delete[] data;
        data = newdata;
        capacity = newCapacity;
    }

public:
    Arr() : data(nullptr), size(0), capacity(2) {
        data = new T[capacity];
    }

    ~Arr() {
        delete[] data;
    }

    // Copy constructor
    Arr(const Arr& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    // Move constructor
    Arr(Arr&& other) noexcept {
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    // Copy assignment
    Arr& operator=(const Arr& other) {
        if (this != &other) {
            T* newdata = new T[other.capacity];

            for (size_t i = 0; i < other.size; i++)
                newdata[i] = other.data[i];

            delete[] data;

            data = newdata;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    // Move assignment
    Arr& operator=(Arr&& other) noexcept {
        if (this != &other) {
            delete[] data;

            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Append (copy)
    void append(const T& x) {
        if (size == capacity)
            resize(capacity * 2);

        data[size++] = x;
    }

    // Append (move)
    void append(T&& x) {
        if (size == capacity)
            resize(capacity * 2);

        data[size++] = std::move(x);
    }

    void pop() {
        if (size > 0) {
            size--;

            if (size <= capacity / 4 && capacity > 2)
                resize(capacity / 2);
        }
    }

    T& operator[](size_t index) {
        if (index >= size)
            throw out_of_range("Index out of bounds");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size)
            throw out_of_range("Index out of bounds");
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        size = 0;
    }

    void print() const {
        cout << "[";
        for (size_t i = 0; i < size; i++) {
            if (i) cout << ", ";
            cout << data[i];
        }
        cout << "]\n";
    }
};

int main() {

    Arr<int> A;
    A.append(1);
    A.print();
    A.append(1);
    A.print();
    A.append(1);
    A.print();
    A.append(1);
    A.print();

    A.pop();
    A.print();

    return 0;
}