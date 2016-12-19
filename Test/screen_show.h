#ifndef SCREEN_SHOW_H
#define SCREEN_SHOW_H
#include <iostream>
void displayArr(int arr[],int length)
{
    for(int i = 0; i != length;++i)
    {
        std::cout << *(arr + i) <<" ";
    }
    std::cout << std::endl;
}
#endif // SCREEN_SHOW_H
