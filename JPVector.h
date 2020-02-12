//
// Created by jacks on 2/12/2020.
//

#ifndef INC_20S_PA02_AUTOINDEXER_JPVECTOR_H
#define INC_20S_PA02_AUTOINDEXER_JPVECTOR_H

using namespace std;

template <class T>
class JPVector{
    private:
        T* data;
        int capacity;
        int max_capacity;
    public:
        JPVector();
        JPVector(int size);
        JPVector(const JPVector<T>& vector);
        ~JPVector();
        JPVector<T>& operator=(const JPVector<T>&);
        void resize();
        void push_back(const T& data);
        void pop_back();
        T& operator[](int index);
        int size();
        int max_size();

};

template<class T>
JPVector<T>::JPVector() {
    data = new T[1];
    capacity = 0;
    max_capacity = 1;
}

template<class T>
JPVector<T>::JPVector(int Size) {
    capacity = Size;
    max_capacity = Size;
    data = new T[Size];
}

template<class T>
JPVector<T>::JPVector(const JPVector<T> &vector) {
    capacity = vector.capacity;
    max_capacity = vector.max_capacity;
    delete[] data;
    data = new T[max_capacity];
    for(int i = 0; i <= capacity; i++){
        data[i] = vector[i];
    }
}

template<class T>
JPVector<T>::~JPVector(){
    if(data != NULL){
        delete[] data;
    }
}

template<class T>
JPVector<T>& JPVector<T>::operator=(const JPVector<T> & jpVector) {
    capacity = jpVector.capacity;
    max_capacity = jpVector.max_capacity;
    int i = 0;
    for(int i = 0;  i <= capacity; i++){

    }
}


template<class T>
void JPVector<T>::resize() {
    T* temp = new T[max_capacity*2];
    for(int i = 0; i < max_capacity; i++){
        temp[i] = data[i];
    }
    max_capacity *= 2;
    delete[] data;
    data = temp;
}

template<class T>
void JPVector<T>::push_back(const T &data) {}

template<class T>
void JPVector<T>::pop_back() {}

template<class T>
T &JPVector<T>::operator[](int index) {}

template<class T>
int JPVector<T>::size() {
    return capacity;
}
template<class T>
int JPVector<T>::max_size() {
    return max_capacity;
}


#endif //INC_20S_PA02_AUTOINDEXER_JPVECTOR_H
