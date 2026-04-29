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
        vector(const vector &other);
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
    vector<T>::vector() : data(nullptr), capacity(0), size(0) { }

    template<typename T>
    vector<T>::~vector() {
        for (size_t i = 0; i < size; i++) {
            std::destroy_at(data + i);
        }
        alloc.deallocate(data, capacity);
    }

    template<typename T>
    vector<T>::vector(const vector &other) : capacity(other.capacity), size(other.size) {
        if (other.data == nullptr) {
            data = nullptr;
            return;
        }
        data = alloc.allocate(capacity);
        for (size_t i = 0; i < size; i++) {
            std::construct_at(data + i, other.data[i]);
        }
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
            size_t new_cap = capacity == 0 ? 1 : capacity * 2;
            T *new_data = alloc.allocate(new_cap);
            for (size_t i = 0; i < size; i++) {
                std::construct_at(new_data + i, std::move(data[i]));
            }
            for (size_t i = 0; i < size; i++) {
                std::destroy_at(data + i);
            }
            if (data != nullptr) alloc.deallocate(data, capacity);
            data = new_data;
            capacity = new_cap;
        }
        std::construct_at(data + size, element);
        size++;
    }

    template<typename T>
    void vector<T>::erase(T *it) {
        if (it < begin() || it >= end()) return;
        size_t idx = it - data;
        for (size_t i = idx; i < size - 1; i++) {
            data[i] = std::move(data[i+1]);
        }
        std::destroy_at(data + size - 1);
        size--;
    }

    template<typename T>
    void vector<T>::reserve(size_t n) {
        if (n <= capacity) return;
        T *new_data = alloc.allocate(n);
        for (size_t i = 0; i < size; i++) {
            std::construct_at(new_data + i, std::move(data[i]));
        }
        for (size_t i = 0; i < size; i++) {
            std::destroy_at(data + i);
        }
        if (data != nullptr) alloc.deallocate(data, capacity);
        data = new_data;
        capacity = n;
    }

    template<typename T>
    void vector<T>::resize(size_t n, const T &val) {
        if (n < size) {
            for (size_t i = n; i < size; i++) {
                std::destroy_at(data + i);
            }
            size = n;
        }
        else if (n > size) {
            if (n > capacity) {
                if (capacity == 0) capacity = 1;
                size_t new_cap = capacity;
                while (new_cap < n) {
                    new_cap *= 2;
                }

                T *new_data = alloc.allocate(new_cap);
                for (size_t i = 0; i < size; i++) {
                    std::construct_at(new_data + i, std::move(data[i]));
                }
                for (size_t i = 0; i < size; i++) {
                    std::destroy_at(data + i);
                }
                if (data != nullptr) alloc.deallocate(data, capacity);
                data = new_data;
                capacity = new_cap;
                for (size_t i = size; i < n; i++) {
                    std::construct_at(data + i, val);
                }
            }
            else {
                for (size_t i = size; i < n; i++) {
                   std::construct_at(data + i, val);
                }
            }
            size = n;
        }

        return;
    }


}


#endif // MYTL_VECTOR_H
