#ifndef TINYSTL_STRING_H
#define TINYSTL_STRING_H
#include "Algorithm.h"
#include "Allocator.h"
namespace TinySTL
{
template<typename CharType,typename Alloc = alloc>
class BasicString
{
public:
    typedef CharType value_type;
    typedef value_type* pointer;
    typedef size_t  size_type;
    typedef pointer iterator;
public:
    BasicString():data_(nullptr){}
    BasicString(char* ptr):data_(ptr){}
    BasicString(BasicString& str):data_(str.data_){}
private:
    pointer data_;
};
}

#endif // TINYSTL_STRING_H
