#include "../Algorithm.h"
#include "screen_show.h"
void test_permutation()
{
    int arr[] = {1,2,3,4,5};
    displayArr(arr,5);
    TinySTL::next_permutation(arr,arr+5);
    displayArr(arr,5);
    TinySTL::pre_permutation(arr,arr+5);
    displayArr(arr,5);
}

