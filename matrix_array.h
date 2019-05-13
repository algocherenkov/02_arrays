#pragma once
#include <type_traits>
#include <cstring>
#include "vector_array.h"
#include "single_array.h"
#include <cassert>

template<typename T>
class MatrixArray: public IArray<T> {
private:
    SingleArray<VectorArray<T>> m_array;
    int m_size{0};
    int m_capacity{10};

public:
    MatrixArray() = default;
    explicit MatrixArray(int initLength):
        m_capacity(initLength)
    {}

    int size() override {
        return m_size;
    }

    void add(T item) override {
        if(m_size == m_array.size()*m_capacity)
            m_array.add(VectorArray<T>(m_capacity));
        m_array.get(m_size/m_capacity).add(item);
        m_size++;
    }

    T get(int index) override {
        return m_array.get(index/m_capacity).get(index % m_capacity);
    }

    void add(T item, int index) override {

    }

    void resize(int index) {

    }

    T remove(int index) {

    }
};
