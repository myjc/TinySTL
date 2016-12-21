#ifndef SORT_TEST_H
#define SORT_TEST_H
#include "screen_show.h"
#include "../Algorithm.h"
#include <vector>
void test_bubble_sort()
{
    std::cout << "test bubble_sort" << std::endl;
    int arr1[] = {9,8,7,6,5,4,3,2,1};

    TinySTL::bubble_sort(arr1,arr1+9);
    displayArr(arr1,9);
    std::vector<int> ivec;
    ivec.reserve(100);
    for(int i = 0 ; i != 100; ++i)
    {
        ivec.push_back(100-i);
    }
    for(int j : ivec)
        std::cout << j << " ";
    std::cout <<"\n";
    TinySTL::bubble_sort(ivec.begin(),ivec.end());
    for(int j : ivec)
        std::cout << j << " ";
    std::cout <<"\n";
}
void test_insertion_sort()
{
    std::cout << "test insertion_sort" << std::endl;
    int arr1[] = {9,8,7,6,5,4,3,2,1};

    TinySTL::insertion_sort(arr1,arr1+9);
    displayArr(arr1,9);
    std::vector<int> ivec;
    ivec.reserve(100);
    for(int i = 0 ; i != 100; ++i)
    {
        ivec.push_back(100-i);
    }
    for(int j : ivec)
        std::cout << j << " ";
    std::cout <<"\n";
    TinySTL::insertion_sort(ivec.begin(),ivec.end());
    for(int j : ivec)
        std::cout << j << " ";
    std::cout <<"\n";
}
void test_sort()
{
    test_insertion_sort();
    test_bubble_sort();
}

#endif // SORT_TEST_H
