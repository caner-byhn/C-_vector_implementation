#ifndef MYTL_VECTOR_H
#define MYTL_VECTOR_H

#include <cstddef>
#include <iostream>
#include <cassert>

namespace mytl {

    template<typename T>
    class vector {
    private:
        T *data;
        size_t capacity;
        size_t size;
    public:
        vector();
        ~vector();
        T *begin();
        T *end();
        T operator[](const size_t idx);
        void push_back(const T &element);
        void erase(T *it);
    };

    template<typename T>
    vector<T>::vector() : capacity(256), size(0){
        data = new T[capacity];
    }

    template<typename T>
    vector<T>::~vector() {
        delete[] data;
    }

    template<typename T>
    T *vector<T>::begin() {
        return data;
    }

    template<typename T>
    T *vector<T>::end() {
        return data + size;
    }

    template<typename T>
    T vector<T>::operator[](const size_t idx) {
        assert(idx < size);
        return data[idx];
    }

    template<typename T>
    void vector<T>::push_back(const T &element) {
        if (size >= capacity) {
            T *new_data = new T[capacity*2];
            for (size_t i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity *= 2;
        }
        data[size] = element;
        size++;
    }

    template<typename T>
    void vector<T>::erase(T *it) {
        size_t idx = it - data;
        if (it < begin() || it >= end()) return;
        for (size_t i = idx; i < size - 1; i++) {
            data[i] = data[i+1];
        }
        size--;
    }

}


#endif // MYTL_VECTOR_H
