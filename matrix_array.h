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

        if(m_size == m_array.size()*m_capacity)
            m_array.add(VectorArray<T>(m_capacity));

        //take all elements which should be moved in other collection
        SingleArray<T> elementsForMove;

        for(int i = index/m_capacity; i <= m_array.size(); i++)
        {
            if(m_array.get(i).size() == m_capacity)
            {
                T lastElement = m_array.get(i).get(m_capacity - 1);
                m_array.get(i).remove(m_capacity - 1);
                elementsForMove.add(lastElement);
            }
        }

        //put the item into position
        m_array.get(index/m_capacity).add(item, index % m_capacity);

        //now move elementsForMove to new places in arrays
        if(elementsForMove.size())
        {
            if(elementsForMove.size() != (m_array.size() - index/m_capacity - 1))
                m_array.add(VectorArray<T>(m_capacity));

            int j = 0;
            for(int i = index/m_capacity + 1; i <= m_array.size(); i++, j++)
                m_array.get(i).add(elementsForMove.get(j), 0);
        }

        m_size++;
    }    

    T remove(int index) {
        assert(index > 0 && index < m_size);

        T result = get(index);
        m_array.get(index/m_capacity).remove(index % m_capacity);
        m_size--;
        return result;
    }
};
