#pragma once
#include "iarray.h"
#include <type_traits>
#include <cstring>
#include <cassert>

template<typename T>
class VectorArray: public IArray<T> {
private:
    T* m_dataPointer{nullptr};
    int m_size{0};
    int m_vectorValue{10};
public:
    VectorArray() = default;
    VectorArray(int initLength):
        m_vectorValue(initLength)
    {}

    ~VectorArray()
    {
        if(m_dataPointer)
            delete [] m_dataPointer;
    }

    int size() override {
        return m_size;
    }

    void add(T item) override {
        if(m_size % m_vectorValue == 0)
            resize();
        m_size++;
        *(m_dataPointer + m_size - 1) = item;
    }

    T get(int index) override {
        return static_cast<T>(*(m_dataPointer + index));
    }

    void resize() {
        T* temp = new T[m_size + m_vectorValue];
        if(m_dataPointer) {
            memcpy(temp, m_dataPointer, sizeof(T)*m_size);
            delete [] m_dataPointer;
        }        
        m_dataPointer = temp;
    }

    void add(T item, int index) override {
        bool dataCopied{false};

        if(m_size % m_vectorValue == 0)
            dataCopied = resize(index);

        if(!dataCopied)
            memcpy(m_dataPointer + index + 1, m_dataPointer + index, sizeof(T)*(m_size - index));

        *(m_dataPointer + index) = item;

        m_size++;
    }

    bool resize(int index) {
        assert(index > 0 && index < m_size);
        bool dataCopied = false;

        T* temp = new T[m_size + m_vectorValue];
        if(m_dataPointer) {
            memcpy(temp, m_dataPointer, sizeof(T)*(index));
            memcpy(temp + index + 1, m_dataPointer + index, sizeof(T)*(m_size - index));
            delete [] m_dataPointer;
            dataCopied = true;
        }
        m_dataPointer = temp;
        return dataCopied;
    }

    T remove(int index) {
        assert(index > 0 && index < m_size);
        T result = *(m_dataPointer + index);
        memcpy(m_dataPointer + index, m_dataPointer + index + 1, sizeof(T)*(m_size - index));
        m_size--;
        return result;
    }
};
