#include <iostream>
#include "matrix_array.h"
#include "factor_array.h"
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>
#include <chrono>

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

template<typename T>
void testAddArray(IArray<T>& array, int total)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < total; i++)
        array.add(i);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << "array " << typeid (array).name() << " " << __FUNCTION__ << " " << duration << std::endl;
}

template<typename T>
void testAddByIndexArray(IArray<T>& array, T item, int position)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    array.add(item, position);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << "array " << typeid (array).name() << " " << __FUNCTION__ << " " << duration << std::endl;
}

template<typename T>
T testRemoveByIndexArray(IArray<T>& array, int position)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    auto result = array.remove(position);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << "array " << typeid (array).name() << " " << __FUNCTION__ << " " << duration << std::endl;

    return result;
}

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(arrays_test_for_basic_add_operation)
{
    constexpr int ELEMENTS_NUMBER = 10000;

    SingleArray<int> sarray;
    testAddArray<int>(sarray, ELEMENTS_NUMBER);

    FactorArray<int, 50> farray(10);
    testAddArray<int>(farray, ELEMENTS_NUMBER);

    VectorArray<int> varray(10);
    testAddArray<int>(varray, ELEMENTS_NUMBER);

    MatrixArray<int> marray1(100);
    testAddArray<int>(marray1, ELEMENTS_NUMBER);

    MatrixArray<int> marray2(1000);
    testAddArray<int>(marray2, ELEMENTS_NUMBER);

    MatrixArray<int> marray3(10000);
    testAddArray<int>(marray3, ELEMENTS_NUMBER);
}

BOOST_AUTO_TEST_CASE(arrays_test_for_add_and_remove_by_index_operation)
{
    constexpr int POSITION = 3;
    int item = 1;
    SingleArray<int> sarray;
    testAddArray<int>(sarray, 10);
    testAddByIndexArray<int>(sarray, item, POSITION);
    auto result = testRemoveByIndexArray<int>(sarray, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result is different");

    VectorArray<int> varray(10);
    testAddArray<int>(varray, 9);
    testAddByIndexArray<int>(varray, item, POSITION);
    result = testRemoveByIndexArray<int>(varray, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result is different");

    VectorArray<int> varray2(10);
    testAddArray<int>(varray2, 10);
    testAddByIndexArray<int>(varray2, item, POSITION);
    result = testRemoveByIndexArray<int>(varray2, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result is different");

    FactorArray<int, 10> farray(10);
    testAddArray<int>(farray, 9);
    testAddByIndexArray<int>(farray, item, POSITION);
    result = testRemoveByIndexArray<int>(farray, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result is different");

    FactorArray<int, 10> farray2(10);
    testAddArray<int>(farray2, 10);
    testAddByIndexArray<int>(farray2, item, POSITION);
    result = testRemoveByIndexArray<int>(farray2, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result is different");

    MatrixArray<int> marray(3);
    testAddArray<int>(marray, 10);
    testAddByIndexArray<int>(marray, item, POSITION);
    result = testRemoveByIndexArray<int>(marray, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result is different");
}
BOOST_AUTO_TEST_SUITE_END()
