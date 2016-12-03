#ifndef TINYSTL_ALGORITHM_H
#define TINYSTL_ALGORITHM_H
#include <cstring>
#include <cassert>
#include"Iterator.h"
#include"Utility.h"
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
//for_each
template<typename InputIterator, typename UnaryPred>
void for_each(InputIterator begin, InputIterator end, UnaryPred pred)
{
    while(begin++ != end)
    {
        pred(*begin);
    }
}
//mismatch 要求序列2长度不小于序列1,否则发生未定义行为
template<typename InputIterator1,typename InputIterator2>
Pair<InputIterator1,InputIterator2> mismatch(InputIterator1 begin1,InputIterator1 end1, InputIterator2 begin2)
{
    while(begin1 != end1)
    {
        if(*begin1 == *begin2)
        {
            ++begin1;
            ++begin2;
        }
    }
    return make_pair(begin1,begin2);
}
template<typename InputIterator1,typename InputIterator2,typename BinaryPred>
Pair<InputIterator1,InputIterator2> mismatch(InputIterator1 begin1,InputIterator1 end1,
                                             InputIterator2 begin2,BinaryPred pred)
{
    while(begin1 != end1)
    {
        if(pred(*begin1,*begin2))
        {
            ++begin1;
            ++begin2;
        }
    }
    return make_pair(begin1,begin2);
}
//equal 要求序列2长度不小于序列1,否则发生未定义行为
template<typename InputIterator1,typename InputIterator2>
bool equal(InputIterator1 begin1,InputIterator1 end1, InputIterator2 begin2)
{
    while(begin1 != end1)
    {
        if(*begin1 == *begin2)
        {
            ++begin1;
            ++begin2;
        }
        else
        {
            return false;
        }
    }
    return true;
}
template<typename InputIterator1,typename InputIterator2,typename BinaryPred>
bool equal(InputIterator1 begin1,InputIterator1 end1, InputIterator2 begin2,BinaryPred pred)
{
    while(begin1 != end1)
    {
        if(pred(*begin1,*end1))
        {
            ++begin1;
            ++begin2;
        }
        else
        {
            return false;
        }
    }
    return true;
}

//fill(begin,end,val)
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
//fill_n(begin,n,val)
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
distance_aux(InputIterator begin,InputIterator end,input_iterator_tag)
{
    typedef typename IteratorTraits<InputIterator>::difference_type difference_type;
    difference_type dis = 0;
    while(begin++ != end) ++dis;
    return dis;
}
template<typename RandomAccessIterator>
typename IteratorTraits<RandomAccessIterator>::difference_type
distance_aux(RandomAccessIterator begin,RandomAccessIterator end,random_access_iterator_tag)
{
    return end - begin;
}
template<typename Iterator>
typename IteratorTraits<Iterator>::difference_type
distance(Iterator begin,Iterator end)
{
    typedef typename IteratorTraits<Iterator>::iterator_category iterator_category;
    return distance_aux(begin,end,iterator_category());

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
inline InputIterator find(InputIterator begin,InputIterator end,const T& val)
{
    while (begin != end && *begin != val) ++begin;
    return begin;
}
//find_if
template<typename InputIterator,typename Func>
inline InputIterator find_if(InputIterator begin, InputIterator end, Func func)
{
    while(begin != end && !(func(*begin))) ++begin;
    return begin;
}
//find_if_not
template<typename InputIterator,typename Func>
inline InputIterator find_if_not(InputIterator begin, InputIterator end, Func func)
{
    while(begin != end && func(*begin)) ++begin;
    return begin;
}
//count
template<typename InputIterator,typename T>
inline typename IteratorTraits<InputIterator>::difference_type
count(InputIterator begin,InputIterator end,const T& val)
{
    typedef typename IteratorTraits<InputIterator>::difference_type Diff;
    Diff quantity = 0;
    while (begin != end)
    {
        if(*begin == val)
             ++quantity;
        ++begin;
    }
    return quantity;
}
//count_if
template<typename InputIterator,typename Func>
inline typename IteratorTraits<InputIterator>::difference_type
count_if(InputIterator begin,InputIterator end,Func func)
{
    typedef typename IteratorTraits<InputIterator>::difference_type Diff;
    Diff quantity = 0;
    while (begin != end)
    {
        if(func(*begin))
             ++quantity;
        ++begin;
    }
    return quantity;
}
//all_of
template<typename InputIterator,typename UnaryPred>
inline bool all_of(InputIterator begin,InputIterator end,UnaryPred pred)
{
    while(begin != end)
    {
        if(!pred(*begin))
            return false;
        ++begin;
    }
    return true;
}
// none_of
template<typename InputIterator,typename UnaryPred>
inline bool none_of(InputIterator begin,InputIterator end,UnaryPred pred)
{
    while(begin != end)
    {
        if(pred(*begin))
            return false;
        ++begin;
    }
    return true;
}
//any_of
template<typename InputIterator,typename UnaryPred>
inline bool any_of(InputIterator begin,InputIterator end,UnaryPred pred)
{
    while(begin != end)
    {
        if(pred(*begin))
            return true;
        ++begin;
    }
    return false;
}
//2.查找重复值算法
//adjacent_find
template<typename ForwardItertor>
inline ForwardItertor adjacent_find(ForwardItertor begin, ForwardItertor end)
{
    if(begin == end) return end;
    ForwardItertor curr = begin;
    while(++curr != end)
    {
        if(*begin == *curr)
            return begin;
        ++begin;
    }
    return end;
}
template<typename ForwardIterator,typename BinaryPred>
inline ForwardIterator adjacent_find(ForwardIterator begin, ForwardIterator end,BinaryPred pred)
{
    if(begin == end) return end;
    ForwardIterator curr = begin;
    while(++curr != end)
    {
        if(pred(begin,curr))
            return begin;
        ++begin;
    }
    return end;
}
//search_n
template<typename ForwardItertor,typename T>
ForwardItertor search_n(ForwardItertor begin, ForwardItertor end,size_t nobjs,const T& val)
{
    ForwardItertor iter = find(begin,end,val);
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
ForwardItertor search_n(ForwardItertor begin, ForwardItertor end,size_t nobjs,const T& val,BinaryPred pred)
{
    ForwardItertor iter = begin;
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
//search
template<typename ForwardIterator1,typename ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 begin1,ForwardIterator1 end1,
                       ForwardIterator2 begin2,ForwardIterator2 end2)
{
    typedef typename IteratorTraits<ForwardIterator1>::difference_type Distance1;
    typedef typename IteratorTraits<ForwardIterator2>::difference_type Distance2;

    ForwardIterator1 iter1 = begin1;
    ForwardIterator2 iter2 = begin2;
    Distance1 dist1 = TinySTL::distance(begin1,end1);//序列1长度
    Distance2 dist2 = TinySTL::distance(begin2,end2);//序列2长度
    if(dist1 < dist2) //序列1长度小于序列2
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
            iter1 = ++begin1;
            iter2 = begin2;
            --dist1;
            if(dist1 < dist2)////序列1剩余长度小于序列2
            {
                return end1;
            }
        }
    }
    return begin1;//found
}
template<typename ForwardIterator1,typename ForwardIterator2,typename BinaryPred>
ForwardIterator1 search(ForwardIterator1 begin1,ForwardIterator1 end1,
                       ForwardIterator2 begin2,ForwardIterator2 end2,
                        BinaryPred pred)
{
    typedef typename IteratorTraits<ForwardIterator1>::difference_type Distance1;
    typedef typename IteratorTraits<ForwardIterator2>::difference_type Distance2;

    ForwardIterator1 iter1 = begin1;
    ForwardIterator2 iter2 = begin2;
    Distance1 dist1 = TinySTL::distance(begin1,end1);//序列1长度
    Distance2 dist2 = TinySTL::distance(begin2,end2);//序列2长度
    if(dist1 < dist2) //序列1长度小于序列2
    {
        return end1;
    }
    while(iter2 != end2)
    {

        if(pred(*iter1,*iter2))
        {
            ++iter1;
            ++iter2;
        }
        else
        {
            iter1 = ++begin1;
            iter2 = begin2;
            --dist1;
            if(dist1 < dist2)////序列1剩余长度小于序列2
            {
                return end1;
            }
        }
    }
    return begin1;//found
}
//find_end
//TODO:使用search和反向迭代器实现 find_end

/*******************************************************************************************************/
/**********************二分搜索算法,要求序列元素已经有序(只实现使用“<”比较的版本)****************************/
//lower_bound 返回指向第一个大于等于给定值的迭代器，不存在则返回end
template<typename RandomAccessIterator,typename T>
RandomAccessIterator lower_bound_aux(RandomAccessIterator begin,RandomAccessIterator end,
                                    const T& val,random_access_iterator_tag)
{
    typedef IteratorTraits<RandomAccessIterator>::difference_type Distance;
    Distance length= end - begin;
    Distance half = length / 2;
    RandomAccessIterator middle =  begin + half;
    while(length > 0)
    {
        if(*middle < val)
        {
            begin = ++middle;
            length = length - half -1;
        }
        else
        {
            length = half;
        }
        half = length / 2;
        middle = begin + half;
    }
    return begin;
}
template<typename ForwardIterator,typename T>
ForwardIterator lower_bound_aux(ForwardIterator begin,ForwardIterator end,
                                    const T& val,forward_iterator_tag)
{
    typedef IteratorTraits<ForwardIterator>::difference_type Distance;
    Distance length= distance(begin,end);
    Distance half = length / 2;
    ForwardIterator middle =  begin;
    advance(middle,half);
    while(length > 0)
    {
        if(*middle < val)
        {
            begin = ++middle;
            length = length - half -1;
        }
        else
        {
            length = half;
        }
        half = length / 2;
        advance(middle,half);
    }
    return begin;
}
template<typename Iterator,typename T>
Iterator lower_bound(Iterator begin,Iterator end,
                                    const T& val)
{
    typedef typename IteratorTraits<Iterator>::iterator_category iterator_category;
    return lower_bound_aux(begin,end,val,iterator_category);
}
//upper_bound 返回指向第一个大于给定值的迭代器，不存在则返回end
template<typename RandomAccessIterator,typename T>
RandomAccessIterator upper_bound_aux(RandomAccessIterator begin,RandomAccessIterator end,
                                    const T& val,random_access_iterator_tag)
{
    typedef IteratorTraits<RandomAccessIterator>::difference_type Distance;
    Distance length= end - begin;
    Distance half = length / 2;
    RandomAccessIterator middle =  begin + half;
    while(length > 0)
    {
        if(val < *middle)
        {
            length = half;
        }
        else
        {
            begin = ++middle;
            length = length - half -1;
        }
        half = length / 2;
        middle = begin + half;
    }
    return begin;
}
template<typename ForwardIterator,typename T>
ForwardIterator upper_bound_aux(ForwardIterator begin,ForwardIterator end,
                                    const T& val,forward_iterator_tag)
{
    typedef IteratorTraits<ForwardIterator>::difference_type Distance;
    Distance length= distance(begin,end);
    Distance half = length / 2;
    ForwardIterator middle =  begin;
    advance(middle,half);
    while(length > 0)
    {
        if(val < *middle)
        {
            length = half;
        }
        else
        {
            begin = ++middle;
            length = length - half -1;
        }
        half = length / 2;
        advance(middle,half);
    }
    return begin;
}
template<typename Iterator,typename T>
Iterator upper_bound(Iterator begin,Iterator end,
                                    const T& val)
{
    typedef typename IteratorTraits<Iterator>::iterator_category iterator_category;
    return upper_bound_aux(begin,end,val,iterator_category);
}

//binary_search
template<typename ForwardIterator,typename T>
bool binary_search(ForwardIterator begin,ForwardIterator end,const T& val)
{
    ForwardIterator iter = lower_bound(begin,end,val);
    return (iter != end) && !(val < *iter);
}
}//namesapce TinySTL
#endif // ALGORITHM_H
