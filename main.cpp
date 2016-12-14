#include <iostream>   
#include <vector>
#include "Algorithm.h"
#include<algorithm>
using namespace std;
void display(int arr[],int length)
{
    for(int i = 0; i != length;++i)
    {
        cout << *(arr + i) <<" ";
    }
    cout << std::endl;
}

int main()
{
    int arr[] = {9,8,7,6,5,4,3,2,1,10};
    int length = sizeof(arr) / sizeof(int);
    cout << length << endl;
    display(arr,length);
    std::push_heap(arr,arr+10);
    display(arr,length);
    std::pop_heap(arr,arr+10);
    display(arr,length);
    std::sort_heap(arr,arr+9);
    display(arr,length);
    std::make_heap(arr,arr+10);
    display(arr,length);
}
