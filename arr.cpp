#include <iostream>
using namespace std;

template <typename T>
class Arr{

    T *data;
    int size;
    int capacity;

    void resize(int newCapacity){
        T *newdata = new T[newCapacity];

        for (size_t i=0; i<size; i++){
            newdata[i] = data[i];
        }
        delete[] data;
        data = newdata;
        capacity = newCapacity;
    }

    public:

    Arr(){
        size = 0;
        capacity = 2;
        data = new T[capacity];
    }

    ~Arr(){
        delete[] data;
    }

    /*
    void append(const T& x){
        if (size == capacity){
            resize(capacity + capacity/8 + 5);
        }
        //data[size++] = x;
        new (&data[size]) T(x);
        size++;
    }
    */

    template <typename... Args>
    void append(Args&&... args) {
        if (size == capacity)
            resize(capacity + capacity/8 + 5);
        new (&data[size]) T(std::forward<Args>(args)...);
        size++;
    }

    void pop(){
        if (size > 0){
            size--;

            if (size <= capacity/4 && capacity > 2) {
                resize(capacity/2 + 2);
            }

        }
    }

    T& operator[](int index){
        if(index < 0 || index >= size)
            throw out_of_range("Index out of bounds");
        return data[index];
    }

    int getSize() const{
        return size;
    }

    void print() const{
        cout << "[";
        for (int i=0; i<size; i++){
            cout << data[i];
            if (i<size-1){
                cout << ", ";
            }
        }

        cout << "]" << endl;
    }

    Arr(Arr&& other) {
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Arr(const Arr& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    Arr& operator=(const Arr& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    Arr& operator=(Arr&& other) {
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