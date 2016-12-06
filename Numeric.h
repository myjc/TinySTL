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
OutputIterator partial_sum(InputIterator begin, InputIterator end, OutputIterator dest)
{
    if(begin == end) return dest;
    typedef typename IteratorTraits<InputIterator>::value_type value_type;
    value_type val = *begin;
    while(begin != end)
    {
        *dest = val;
        ++begin;
        ++dest;
        val += *begin;
    }
    return dest;
}
template<typename InputIterator,typename OutputIterator,typename BinaryPred>
OutputIterator partial_sum(InputIterator begin, InputIterator end, OutputIterator dest,BinaryPred pred)
{
    if(begin == end) return dest;
    typedef typename IteratorTraits<InputIterator>::value_type value_type;
    value_type val = *begin;
    while(begin != end)
    {
        *dest = val;
        ++begin;
        ++dest;
        val = pred(val,*end);
    }
    return dest;
}
//adjacent_differance
template<typename InputIterator,typename OutputIterator>
OutputIterator adjacent_differance(InputIterator begin, InputIterator end, OutputIterator dest)
{
    if(begin == end) return dest;
    *dest = *begin;
    InputIterator curr = begin;
    ++curr;
    while(curr != end)
    {
        *(++dest) = *curr - *begin;
        ++begin;
        ++curr;
    }
    return ++dest;
}
template<typename InputIterator,typename OutputIterator,typename BinaryPred>
OutputIterator adjacent_differance(InputIterator begin, InputIterator end,
                                   OutputIterator dest,BinaryPred pred)
{
    if(begin == end) return dest;
    *dest = *begin;
    InputIterator curr = begin;
    ++curr;
    while(curr != end)
    {
        *(++dest) = pred(*curr,*begin);
        ++begin;
        ++curr;
    }
    return ++dest;
}
//inner_product
template<typename InputIterator1,typename InputIterator2,typename T>
T inner_product (InputIterator1 begin1,InputIterator1 end1,
                 InputIterator2 begin2,
                 T init)
{
    while(begin1 != end1)
    {
        init = init + (*begin1) * (*begin2);
        ++begin1;
        ++begin2;
    }
    return init;
}
template<typename InputIterator1,typename InoutIterator2,typename T,typename PlusFunc,typename MultiFunc>
T inner_product (InputIterator1 begin1,InputIterator1 end1,
                 InoutIterator2 begin2,T init,
                 PlusFunc plus,MultiFunc multi)
{
    while(begin1 != end1)
    {
        init = plus(init,multi(*begin1,*begin2));
        ++begin1;
        ++begin2;
    }
    return init;
}
}

#endif // TINYSTL_NUMERIC_H
