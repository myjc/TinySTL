#ifndef TINYSTL_NUMERIC_H
#define TINYSTL_NUMERIC_H
#include "Iterator.h"
namespace TinySTL
{
//accumulate
template<typename InputIterator,typename T>
T accumulate(InputIterator begin, InputIterator end, T val)
{
    while(begin != end)
    {
        val += *begin;
        ++begin;
    }
    return val;
}
template<typename InputIterator,typename T,typename BinaryPred>
T accumulate(InputIterator begin, InputIterator end, T val,BinaryPred pred)
{
    while(begin != end)
    {
        val = pred(val,*begin);
        ++begin;
    }
    return val;
}
//iota
template<typename InputIterator,typename T>
void iota(InputIterator begin, InputIterator end, T val)
{
    while(begin != end)
    {
        *begin = val;
        ++val;
        ++begin;
    }
}
//partial_sum
template<typename InputIterator,typename OutputIterator>
void partial_sum(InputIterator begin, InputIterator end, OutputIterator dest)
{
    typedef typename IteratorTraits<InputIterator>::value_type value_type;
    value_type val = *begin;
    while(begin != end)
    {
        *dest = val;
        ++begin;
        val += *begin;
    }
}
template<typename InputIterator,typename OutputIterator,typename BinaryPred>
void partial_sum(InputIterator begin, InputIterator end, OutputIterator dest,BinaryPred pred)
{
    typedef typename IteratorTraits<InputIterator>::value_type value_type;
    value_type val = *begin;
    while(begin != end)
    {
        *dest = val;
        ++begin;
        val = pred(val,*end);
    }
}
}

#endif // TINYSTL_NUMERIC_H
