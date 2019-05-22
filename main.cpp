#include <iostream>
#include "matrix_array.h"
#include "factor_array.h"
#include "priority_queue.h"
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
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();

    std::cout << "array " << typeid (array).name() << " " << __FUNCTION__ << " " << duration << std::endl;
}

template<typename T>
T testGetByIndexArray(IArray<T>& array, int position)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    auto result = array.get(position);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();

    std::cout << "array " << typeid (array).name() << " " << __FUNCTION__ << " " << duration << std::endl;

    return result;
}

template<typename T>
T testRemoveByIndexArray(IArray<T>& array, int position)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    auto result = array.remove(position);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();

    std::cout << "array " << typeid (array).name() << " " << __FUNCTION__ << " " << duration << std::endl;

    return result;
}

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(arrays_operation_time_10000_elements_in_every_array)
{
    constexpr int ELEMENTS_NUMBER = 10000;
    constexpr int POSITION = 5000;
    constexpr int ITEM_VALUE = 73;

    constexpr int FACTOR_1 = 50;
    constexpr int FACTOR_2 = 100;

    constexpr int INIT_LENGTH_1 = 10;
    constexpr int INIT_LENGTH_2 = 100;
    constexpr int INIT_LENGTH_3 = 1000;

    /*------------------------------1------------------------------*/
    SingleArray<int> sarray;
    testAddArray<int>(sarray, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(sarray, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(sarray, POSITION);
    testRemoveByIndexArray<int>(sarray, POSITION);

    VectorArray<int> varray(INIT_LENGTH_1);
    testAddArray<int>(varray, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(varray, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(varray, POSITION);
    testRemoveByIndexArray<int>(varray, POSITION);

    FactorArray<int, FACTOR_1> farray(INIT_LENGTH_1);
    testAddArray<int>(farray, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(farray, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(farray, POSITION);
    testRemoveByIndexArray<int>(farray, POSITION);

    FactorArray<int, FACTOR_2> farray2(INIT_LENGTH_1);
    testAddArray<int>(farray2, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(farray2, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(farray2, POSITION);
    testRemoveByIndexArray<int>(farray2, POSITION);
    /*------------------------------2------------------------------*/

    VectorArray<int> varray2(INIT_LENGTH_2);
    testAddArray<int>(varray2, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(varray2, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(varray2, POSITION);
    testRemoveByIndexArray<int>(varray2, POSITION);

    FactorArray<int, FACTOR_1> farray3(INIT_LENGTH_2);
    testAddArray<int>(farray3, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(farray3, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(farray3, POSITION);
    testRemoveByIndexArray<int>(farray3, POSITION);

    FactorArray<int, FACTOR_2> farray4(INIT_LENGTH_2);
    testAddArray<int>(farray4, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(farray4, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(farray4, POSITION);
    testRemoveByIndexArray<int>(farray4, POSITION);

    /*------------------------------3------------------------------*/

    VectorArray<int> varray3(INIT_LENGTH_3);
    testAddArray<int>(varray3, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(varray3, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(varray3, POSITION);
    testRemoveByIndexArray<int>(varray3, POSITION);

    FactorArray<int, FACTOR_1> farray5(INIT_LENGTH_3);
    testAddArray<int>(farray5, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(farray5, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(farray5, POSITION);
    testRemoveByIndexArray<int>(farray5, POSITION);

    FactorArray<int, FACTOR_2> farray6(INIT_LENGTH_3);
    testAddArray<int>(farray6, ELEMENTS_NUMBER);
    testAddByIndexArray<int>(farray6, ITEM_VALUE, POSITION);
    testGetByIndexArray<int>(farray6, POSITION);
    testRemoveByIndexArray<int>(farray6, POSITION);
}

BOOST_AUTO_TEST_CASE(arrays_test_for_add_and_remove_by_index_operation)
{
    constexpr int POSITION = 3;
    int item = 1;
    SingleArray<int> sarray;
    testAddArray<int>(sarray, 10);
    testAddByIndexArray<int>(sarray, item, POSITION);
    auto result = testRemoveByIndexArray<int>(sarray, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result from SingleArray is different");

    VectorArray<int> varray(10);
    testAddArray<int>(varray, 9);
    testAddByIndexArray<int>(varray, item, POSITION);
    result = testRemoveByIndexArray<int>(varray, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result from VectorArray is different");

    VectorArray<int> varray2(10);
    testAddArray<int>(varray2, 10);
    testAddByIndexArray<int>(varray2, item, POSITION);
    result = testRemoveByIndexArray<int>(varray2, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result from VectorArray is different");

    FactorArray<int, 10> farray(10);
    testAddArray<int>(farray, 9);
    testAddByIndexArray<int>(farray, item, POSITION);
    result = testRemoveByIndexArray<int>(farray, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result from FactorArray from is different");

    FactorArray<int, 10> farray2(10);
    testAddArray<int>(farray2, 10);
    testAddByIndexArray<int>(farray2, item, POSITION);
    result = testRemoveByIndexArray<int>(farray2, POSITION);
    BOOST_CHECK_MESSAGE(item == result, "expected result from FactorArray is different");
}

BOOST_AUTO_TEST_CASE(priority_queue_test)
{
    PriorityQueue<std::string> queue;
    queue.enqueue("sara", 1);
    queue.enqueue("john", 3);
    queue.enqueue("barbara", 2);

    auto result1 = queue.dequeue();
    BOOST_CHECK_MESSAGE(*result1 == "john", "expected result is john");
    auto result2 = queue.dequeue();
    BOOST_CHECK_MESSAGE(*result2 == "barbara", "expected result is barbara");
    auto result3 = queue.dequeue();
    BOOST_CHECK_MESSAGE(*result3 == "sara", "expected result is sara");
    auto result4 = queue.dequeue();
    BOOST_CHECK_MESSAGE(result4 == nullptr, "expected result is nullptr");
}
BOOST_AUTO_TEST_SUITE_END()
