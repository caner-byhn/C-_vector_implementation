#ifndef MYTL_VECTOR_H
#define MYTL_VECTOR_H

#include <cstddef>
#include <iostream>
#include <cassert>
#include <utility>
#include <memory>

namespace mytl {

    template<typename T>
    class vector {
    private:
        std::allocator<T> alloc;
        T *data;
        size_t capacity;
        size_t size;
    public:
        vector();
        ~vector();
        T *begin();
        T *end();
        T &operator[](const size_t idx);
        void push_back(const T &element);
        void erase(T *it);
        void reserve(size_t n);
        void resize(size_t n, const T &val = T{});
        size_t len();
    };

    template<typename T>
    vector<T>::vector() : capacity(256), size(0){
        data = alloc.allocate(capacity);
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
    T &vector<T>::operator[](const size_t idx) {
        assert(idx < size);
        return data[idx];
    }

    template<typename T>
    size_t vector<T>::len() {
        return size;
    }

    template<typename T>
    void vector<T>::push_back(const T &element) {
        if (size >= capacity) {
            T *new_data = alloc.allocate(capacity * 2);
            for (size_t i = 0; i < size; i++) {
                alloc.construct(new_data + i, std::move(data[i]));
            }
            for (size_t i = 0; i < size; i++) {
                alloc.destroy(data + i);
            }
            if (data != nullptr) alloc.deallocate(data, capacity);
            data = new_data;
            capacity *= 2;
        }
        alloc.construct(data + size, element);
        size++;
    }

    template<typename T>
    void vector<T>::erase(T *it) {
        size_t idx = it - data;
        if (it < begin() || it >= end()) return;
        for (size_t i = idx; i < size - 1; i++) {
            data[i] = data[i+1];
        }
        alloc.destroy(data + size - 1);
        size--;
    }

    template<typename T>
    void vector<T>::reserve(size_t n) {
        if (n <= capacity) return;
        T *new_data = alloc.allocate(n);
        for (size_t i = 0; i < size; i++) {
            alloc.construct(new_data + i, std::move(data[i]));
        }
        for (size_t i = 0; i < size; i++) {
            alloc.destroy(data + i);
        }
        if (data != nullptr) alloc.deallocate(data, capacity);
        data = new_data;
        capacity = n;
    }

    template<typename T>
    void vector<T>::resize(size_t n, const T &val) {
        if (n < size) {
            for (size_t i = n; i < size; i++) {
                alloc.destroy(data + i);
            }
            size = n;
        }
        else if (n > size) {
            T *new_data = alloc.allocate(n);
            for (size_t i = 0; i < size; i++) {
                alloc.construct(new_data + i, std::move(data[i]));
            }
            for (size_t i = 0; i < size; i++) {
                alloc.destroy(data + i);
            }
            if (data != nullptr) alloc.deallocate(data, capacity);
            data = new_data;
            capacity = n;
            for (size_t i = size; i < n; i++) {
                alloc.construct(data + i, val);
            }
            size = n;
        }

        return;
    }


}


#endif // MYTL_VECTOR_H
