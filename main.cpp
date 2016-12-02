#include <iostream>
#include "Algorithm.h"
int main()
{
    char str1[] = "abcdefgdefghijkl";
    char str2[] = "defgh";
    char* res = TinySTL::search(str1,str1+12,str2,str2+5);
    std::cout<<res - str1 << std::endl;
}
