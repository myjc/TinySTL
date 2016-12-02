#ifndef TINYSTL_ALGORITHM_H
#define TINYSTL_ALGORITHM_H
#include <cstring>
#include <cassert>
#include"Iterator.h"
namespace TinySTL {

// min max
template <typename T> T max(const T& v1, const T& v2)
{
    return (v1 > v2) ? v1:v2;
}
template<typename T,typename CompareFunc> T max(const T& v1, const T& v2,CompareFunc func)
{
    return (func(v1,v2)) ? v1 :v2;
}
template <typename T> T min(const T& v1, const T& v2)
{
    return (v1 < v2) ? v1 : v2;
}
template<typename T,typename CompareFunc> T min(const T& v1, const T& v2,CompareFunc func)
{
    return (func(v1,v2)) ? v1 :v2;
}

//fill(beg,end,val)
template<typename ForwardIterator,typename T>
void fill(ForwardIterator first,ForwardIterator last,const T& val)
{
    for(; first != last; first++)
        *first = val;
}
inline void fill(char* first, char* last,const char& value)
{
    memset(first, static_cast<unsigned char>(value),last - first);
}
inline void fill(wchar_t* first, wchar_t* last, const wchar_t& value)
{
     memset(first, static_cast<unsigned char>(value),(last - first)*sizeof(wchar_t));
}
//fill_n(beg,n,val)
template<typename ForwardIterator,typename T>
void fill_n(ForwardIterator pos,size_t n,const T& value)
{
    for(;n > 0; n--,pos++)
        *pos = value;
}
inline void fill_n(char* pos, const size_t n,const char& value)
{
    memset(pos,static_cast<unsigned char>(value),n);
}
inline void fill_n(wchar_t *pos, const size_t n, const wchar_t &value)
{
    memset(pos,static_cast<unsigned char>(value),n*sizeof(wchar_t));
}
//distance
template<typename InputIterator>
typename IteratorTraits<InputIterator>::difference_type
distance_aux(InputIterator beg,InputIterator end,input_iterator_tag)
{
    typedef typename IteratorTraits<InputIterator>::difference_type difference_type;
    difference_type dis = 0;
    while(beg++ != end) ++dis;
    return dis;
}
template<typename RandomAccessIterator>
typename IteratorTraits<RandomAccessIterator>::difference_type
distance_aux(RandomAccessIterator beg,RandomAccessIterator end,random_access_iterator_tag)
{
    return end - beg;
}
template<typename Iterator>
typename IteratorTraits<Iterator>::difference_type
distance(Iterator beg,Iterator end)
{
    typedef typename IteratorTraits<Iterator>::iterator_category iterator_category;
    return distance_aux(beg,end,iterator_category());

}

//advance

template<typename InputIterator,typename Distance>
void _advance(InputIterator& iter,Distance n,input_iterator_tag)
{
    assert(n >= 0);
    while(n-- != 0) ++iter;
}
template<typename BidirectionalIterator,typename Distance>
void _advance(BidirectionalIterator& iter,Distance n,bidirectional_iterator_tag)
{
    if(n > 0)
    {
        while(n-- != 0) ++iter;
    }
    else
    {
        while(n++ != 0) --iter;
    }
}
template<typename RandomAccessIterator,typename Distance>
void _advance(RandomAccessIterator& iter,Distance n,random_access_iterator_tag)
{
    if(n > 0)
    {
        iter += n;
    }
    else
    {
        iter -= (-n);
    }
}
template<typename Iterator,typename Distance>
void advance(Iterator& iter,Distance n)
{
    typedef typename IteratorTraits<Iterator>::iterator_category iterator_category;
    _advance(iter,n,iterator_category());
}
//**************************************************************//
//*************************查找对象的算法************************//
//1.简单查找算法
// find
template<typename InputIterator,typename T>
inline InputIterator find(InputIterator beg,InputIterator end,const T& val)
{
    while (beg != end && *beg != val) ++beg;
    return beg;
}
//find_if
template<typename InputIterator,typename Func>
inline InputIterator find_if(InputIterator beg, InputIterator end, Func func)
{
    while(beg != end && !(func(*beg))) ++beg;
    return beg;
}
//find_if_not
template<typename InputIterator,typename Func>
inline InputIterator find_if_not(InputIterator beg, InputIterator end, Func func)
{
    while(beg != end && func(*beg)) ++beg;
    return beg;
}
//count
template<typename InputIterator,typename T>
inline typename IteratorTraits<InputIterator>::difference_type
count(InputIterator beg,InputIterator end,const T& val)
{
    typedef typename IteratorTraits<InputIterator>::difference_type Diff;
    Diff quantity = 0;
    while (beg != end)
    {
        if(*beg == val)
             ++quantity;
        ++beg;
    }
    return quantity;
}
//count_if
template<typename InputIterator,typename Func>
inline typename IteratorTraits<InputIterator>::difference_type
count_if(InputIterator beg,InputIterator end,Func func)
{
    typedef typename IteratorTraits<InputIterator>::difference_type Diff;
    Diff quantity = 0;
    while (beg != end)
    {
        if(func(*beg))
             ++quantity;
        ++beg;
    }
    return quantity;
}
//all_of
template<typename InputIterator,typename UnaryPred>
inline bool all_of(InputIterator beg,InputIterator end,UnaryPred pred)
{
    while(beg != end)
    {
        if(!pred(*beg))
            return false;
        ++beg;
    }
    return true;
}
// none_of
template<typename InputIterator,typename UnaryPred>
inline bool none_of(InputIterator beg,InputIterator end,UnaryPred pred)
{
    while(beg != end)
    {
        if(pred(*beg))
            return false;
        ++beg;
    }
    return true;
}
//any_of
template<typename InputIterator,typename UnaryPred>
inline bool any_of(InputIterator beg,InputIterator end,UnaryPred pred)
{
    while(beg != end)
    {
        if(pred(*beg))
            return true;
        ++beg;
    }
    return false;
}
//2.查找重复值算法
//adjacent_find
template<typename ForwardItertor>
inline ForwardItertor adjacent_find(ForwardItertor beg, ForwardItertor end)
{
    if(beg == end) return end;
    ForwardItertor curr = beg;
    while(++curr != end)
    {
        if(*beg == *curr)
            return beg;
        ++beg;
    }
    return end;
}
template<typename ForwardIterator,typename BinaryPred>
inline ForwardIterator adjacent_find(ForwardIterator beg, ForwardIterator end,BinaryPred pred)
{
    if(beg == end) return end;
    ForwardIterator curr = beg;
    while(++curr != end)
    {
        if(pred(beg,curr))
            return beg;
        ++beg;
    }
    return end;
}
//search_n
template<typename ForwardItertor,typename T>
ForwardItertor search_n(ForwardItertor beg, ForwardItertor end,size_t nobjs,const T& val)
{
    ForwardItertor iter = find(beg,end,val);
    size_t n = nobjs;
    while(n > 0 && iter != end)
    {
        if(*iter == val)
        {
            iter++;
            n--;
        }

        else
        {
            iter = find(++iter,end,val);
            n = nobjs;
        }
    }
    return iter;
}
template<typename ForwardItertor,typename T,typename BinaryPred>
ForwardItertor search_n(ForwardItertor beg, ForwardItertor end,size_t nobjs,const T& val,BinaryPred pred)
{
    ForwardItertor iter = beg;
    while(iter != end)
    {
        if(pred(val,*iter))
            break;
        ++iter;
    }
    size_t n = nobjs;
    while(n > 0 && iter != end)
    {
        if(pred(val,*iter))
        {
            iter++;
            n--;
        }
        else
        {
            while(iter != end)
            {
                if(pred(val,*iter))
                    break;
                ++iter;
            }
            n = nobjs;
        }
    }
    return iter;
}
//3.查找子序列的算法
//find_first_of O(N*M)
template<typename InputIterator,typename ForwardIterator>
InputIterator find_first_of(InputIterator begin1,InputIterator end1,
                            ForwardIterator begin2,ForwardIterator end2)
{
    while(begin1 != end1)
    {
        for(ForwardIterator iter = begin2; iter != end2; ++iter)
        {
            if(*iter == *begin1) return begin1;
        }
        ++begin1;
    }
    return end1;
}
template<typename InputIterator,typename ForwardIterator,typename BinaryPred>
InputIterator find_first_of(InputIterator begin1,InputIterator end1,
                            ForwardIterator begin2,ForwardIterator end2,
                            BinaryPred pred)
{
    while(begin1 != end1)
    {
        for(ForwardIterator iter = begin2; iter != end2; ++iter)
        {
            if(pred(*iter,*begin1)) return begin1;
        }
        ++begin1;
    }
    return end1;
}
template<typename ForwardIterator>
//search
ForwardIterator search(ForwardIterator beg1,ForwardIterator end1,
                       ForwardIterator beg2,ForwardIterator end2)
{
    typedef typename IteratorTraits<ForwardIterator>::difference_type Distance;

    ForwardIterator res = find(beg1,end1,*beg2);
    ForwardIterator iter1 = res;
    ForwardIterator iter2 = beg2;
    Distance dist1 = TinySTL::distance(res,end1);//序列1剩余长度
    Distance dist2 = TinySTL::distance(beg2,end2);//序列2长度
    if(dist1 < dist2) //序列1剩余长度小于序列2
    {
        return end1;
    }
    while(iter2 != end2)
    {

        if(*iter1 == *iter2)
        {
            ++iter1;
            ++iter2;
        }
        else
        {
            res = find(iter1,end1,*beg2);
            iter1 = res;
            iter2 = beg2;
            dist1 =TinySTL::distance(res,end1);
            if(dist1 < dist2)////序列1剩余长度小于序列2
            {
                return end1;
            }
        }
    }
    return res;//found
}
//find_end
}//namesapce TinySTL
#endif // ALGORITHM_H
