//
// Created by jacks on 2/12/2020.
//
#ifndef INC_20S_PA02_AUTOINDEXER_JPVECTOR_H
#define INC_20S_PA02_AUTOINDEXER_JPVECTOR_H

using namespace std;

struct outOfRangeVector : exception {
    const char *what() const noexcept override { return "Index is out of range for JPVector!"; }
};

template<class T>
class JPVector {
private:
    T *data;
    int capacity;
    int max_capacity;

    void resize();

public:
    JPVector();

    explicit JPVector(int size);

    JPVector(JPVector<T> &vector);

    ~JPVector();

    JPVector<T> &operator=(const JPVector<T> &);

    void push_back(const T &data);

    void pop_back();

    T &operator[](int index) const;

    int size();

    int max_size();

    T &at(int index) const;
};

template<class T>
JPVector<T>::JPVector() { //Empty Constructor
    max_capacity = 1;
    capacity = 0;
    data = new T[max_capacity];
}

template<class T>
JPVector<T>::JPVector(int Size) { //Constructor based off of defined size
    capacity = Size;
    max_capacity = Size;
    data = new T[Size];
}

template<class T>
JPVector<T>::JPVector(JPVector<T> &vector) { //Copy Constructor
    capacity = vector.capacity;
    max_capacity = vector.max_capacity;
    data = new T[max_capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = vector[i];
    }
}

template<class T>
JPVector<T>::~JPVector() { //Destructor
    if (data != NULL) {
        delete[] data;
    }
}

template<class T>
JPVector<T> &JPVector<T>::operator=(const JPVector<T> &jpVector) { //Assignment operator from another JPVector
    if (this != &jpVector) {
        delete[] data;
        capacity = jpVector.capacity;
        max_capacity = jpVector.max_capacity;
        data = new T[max_capacity];
        for (int i = 0; i < capacity; i++) {
            data[i] = jpVector.data[i];
        }
    }
    return *this;
}

template<class T>
void JPVector<T>::resize() { //resize used if the vector needs to grow
    T *temp = new T[max_capacity * 2];
    for (int i = 0; i < max_capacity; i++) {
        temp[i] = data[i];
    }
    max_capacity *= 2;
    delete[] data;
    data = temp;
}

template<class T>
void JPVector<T>::push_back(const T &Data) { //adds an element to the end of the vector
    T *temp = new T[capacity + 1];
    for (int i = 0; i < capacity; i++) {
        temp[i] = data[i];
    }
    temp[capacity] = Data;
    delete[] data;
    data = temp;
    capacity += 1;
    if (capacity >= max_capacity) {
        resize();
    }
}

template<class T>
void JPVector<T>::pop_back() { //pops the last element off of the vector
    if (capacity > 0) {
        T *temp = new T[capacity];
        for (int i = 0; i < capacity - 1; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity -= 1;
    }
}

template<class T>
T &JPVector<T>::operator[](int index) const { //subscript operator
    if (!(index < 0 || index >= capacity)) {
        return data[index];
    } else {
        throw outOfRangeVector();
    }
}

template<class T>
T &JPVector<T>::at(int index) const { //subscript operator
    if (!(index < 0 || index >= capacity)) {
        return data[index];
    } else {
        throw outOfRangeVector();
    }
}

template<class T>
int JPVector<T>::size() { //check the size of the vector
    return capacity;
}

template<class T>
int JPVector<T>::max_size() { //check the max_capacity of the vector
    return max_capacity;
}


#endif //INC_20S_PA02_AUTOINDEXER_JPVECTOR_H
