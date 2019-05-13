#pragma once

template<typename T>
class IArray {
public:
    IArray() = default;
    virtual int size() = 0;
    virtual void add(T item) = 0;
    virtual T get(int index) = 0;
    virtual void add(T item, int index) = 0;
    virtual T remove(int index) = 0;
};
