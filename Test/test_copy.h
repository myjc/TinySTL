#ifndef TEST_COPY_H
#define TEST_COPY_H
#include "screen_show.h"
#include "../Algorithm.h"
void test_copy()
{
    std::cout << "test copy_backward" << std::endl;
    int arr1[] = {9,8,7,6,5,4,3,2,1};
    displayArr(arr1,9);
    TinySTL::copy_backward(arr1,arr1+3,arr1+9);
    displayArr(arr1,9);
}

#endif // TEST_COPY_H
