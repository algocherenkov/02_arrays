#pragma once
#include "iarray.h"
#include <type_traits>
#include <cstring>
#include <cassert>

template<typename T>
class SingleArray: public IArray<T> {
private:
    T* m_dataPointer{nullptr};
    int m_size{0};

public:
    SingleArray() = default;
    ~SingleArray()
    {
        if(m_dataPointer)
            delete [] m_dataPointer;
    }

    int size() override {
        return m_size;
    }

    void add(T item) override {
        resize();        
        *(m_dataPointer + m_size) = item;
        m_size++;
    }

    void add(T item, int index) override {
        resize(index);
        *(m_dataPointer + index) = item;
        m_size++;
    }

    T get(int index) override {
        return static_cast<T>(*(m_dataPointer + index));
    }

    T* getPointer(int index) {
        return static_cast<T*>((m_dataPointer + index));
    }

    void resize() {
        T* temp = new T[m_size + 1];
        if(m_dataPointer) {
            memcpy(temp, m_dataPointer, sizeof(T)*m_size);
            delete [] m_dataPointer;
        }
        m_dataPointer = temp;
    }

    void resize(int index) {
        assert(index > 0 && index < m_size);
        T* temp = new T[m_size + 1];
        if(m_dataPointer) {
            memcpy(temp, m_dataPointer, sizeof(T)*(index));
            memcpy(temp + index + 1, m_dataPointer + index, sizeof(T)*(m_size - index));
            delete [] m_dataPointer;
        }
        m_dataPointer = temp;
    }

    T remove(int index) {
        assert(index > 0 && index < m_size);
        auto result = get(index);
        memcpy(m_dataPointer + index, m_dataPointer + index + 1, sizeof(T)*(m_size - index - 1));
        m_size--;
        return result;
    }
};
