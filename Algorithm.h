#ifndef TINYSTL_ALGORITHM_H
#define TINYSTL_ALGORITHM_H
#include <cstring>
#include <cassert>
#include"Iterator.h"
#include"Utility.h"
#include"Functional.h"
#include <iostream>
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
UnaryPred for_each(InputIterator begin, InputIterator end, UnaryPred pred)
{
    while(begin != end)
    {
        pred(*begin);
        ++begin;
    }
    return pred;
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
/*****************************************************************************************/
/*********************************写容器的算法*********************************************/

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
//generate
template<typename OutputIterator,typename GenerateFunc>
void generate(OutputIterator begin,OutputIterator end,GenerateFunc func)
{
    while(begin != end)
    {
        *begin = func();
        ++begin;
    }
}
//generate_n
template<typename OutputIterator,typename Count,typename GenerateFunc>
OutputIterator generate_n(OutputIterator begin,Count n,GenerateFunc func)
{
    while(n > 0)
    {
        *begin = func();
        ++begin;
        --n;
    }
    return begin;
}
// move: c++11,对每个元素调用move，移动到dest开始的序列
template<typename InputIterator,typename OutputIterator>
OutputIterator move(InputIterator begin,InputIterator end,OutputIterator dest)
{
    while(begin != end)
    {
        *dest = TinySTL::move(*begin);
        ++begin;
        ++dest;
    }
    return dest;
}
//move_backward
template<typename BidirectionalIterator1,typename BidirectionalIterator2>
BidirectionalIterator2 move_backward(BidirectionalIterator1 begin,BidirectionalIterator1 end,
                                     BidirectionalIterator2 dest)
{
    if(end == begin)
        return dest;
    while(end != begin)
    {
        *--dest = TinySTL::move(*--end);
    }
    *--dest = TinySTL::move(*--end);
    return dest;
}
//transform
template<typename InputIterator,typename OutputIterator,typename UnaryPred>
OutputIterator transform(InputIterator begin,InputIterator end,OutputIterator dest,UnaryPred func)
{
    while(begin != end)
    {
        *dest = func(*begin);
        ++dest;
        ++begin;
    }
    return dest;
}
template<typename InputIterator1,typename InputIterator2,typename OutputIterator,typename BinaryPred>
OutputIterator transform(InputIterator1 begin1,InputIterator1 end1,
                           InputIterator2 begin2,//该版本要求序列2长度不小于序列1
                           OutputIterator dest,BinaryPred func)
{
    while(begin1 != end1)
    {
        *dest = func(*begin1,*begin2);
        ++dest;
        ++begin1;
        ++begin2;
    }
    return dest;
}
//replace O(N)
template<typename ForwardIterator,typename T>
void replace(ForwardIterator begin,ForwardIterator end,
                            const T& old_val,const T& new_val)
{
    for(; begin != end; ++begin)
    {
        if(*begin == old_val)
           *begin = new_val;
    }
}
//replace_copy O(N)
template<typename InputIterator,typename OutputIterator,typename T>
OutputIterator replace_copy(InputIterator begin,InputIterator end,OutputIterator dest,
                            const T& old_val,const T& new_val)
{
    for(; begin != end; ++begin,++dest)
    {
        if(*begin == old_val)
            *dest = new_val;
        else
            *dest = *begin;
    }
    return dest;
}
//replace_if O(N)
template<typename ForwardIterator,typename UnaryPred,typename T>
void replace_if(ForwardIterator begin,ForwardIterator end,
                            UnaryPred pred,const T& new_val)
{
    for(; begin != end; ++begin)
    {
        if(pred(*begin))
           *begin = new_val;
    }
}
//replace_copy_if O(N)
template<typename InputIterator,typename OutputIterator,typename UnaryPred,typename T>
OutputIterator replace_copy_if(InputIterator begin,InputIterator end,OutputIterator dest,
                            UnaryPred pred,const T& new_val)
{
    for(; begin != end; ++begin,++dest)
    {
        if(pred(*begin))
            *dest = new_val;
        else
            *dest = *begin;
    }
    return dest;
}
//iter_swap
template<typename ForwardIterator1,typename ForwardIterator2>
void iter_swap(ForwardIterator1 iter1,ForwardIterator2 iter2)
{
    typename IteratorTraits<ForwardIterator1>::value_type tmp = *iter1;
    *iter1 = *iter2;
    *iter2 = tmp;
}
//swap_ranges
template<typename ForwardIterator1,typename ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 begin1,ForwardIterator1 end1,ForwardIterator2 begin2)
{
    while (begin1 != end1) {
        TinySTL::iter_swap(begin1,begin2);
        ++begin1;
        ++begin2;
    }
    return begin2;
}
//copy
template<typename RandomAccessIterator,typename OutputIterator>
OutputIterator _copy_rand(RandomAccessIterator begin,RandomAccessIterator end,
                              OutputIterator dest)
{
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type Distance;
    for(Distance n = end - begin; n != 0;--n)
    {
        *dest = *begin;
        ++dest;
        ++begin;
    }
    return dest;
}
template<typename T>
T* _copy_argumentPtr(const T* begin,const T* end,T* dest,_true_type)
{
    memmove(dest,begin,end-begin);
    return dest+(end-begin);
}
template<typename T>
T* _copy_argumentPtr(const T* begin,const T* end,T* dest,_false_type)
{
    return _copy_rand(begin,end,dest);
}
template<typename InputIterator,typename OutputIterator>
OutputIterator _copy_aux(InputIterator begin,InputIterator end,
                              OutputIterator dest,input_iterator_tag)
{
    while(begin != end)
    {
        *dest = *begin;
        ++dest;
        ++begin;
    }
    return dest;
}
template<typename RandomAccessIterator,typename OutputIterator>
OutputIterator _copy_aux(RandomAccessIterator begin,RandomAccessIterator end,
                              OutputIterator dest,random_access_iterator_tag)
{
    return _copy_rand(begin,end,dest);
}
template<typename InputIterator,typename OutputIterator>
struct _copy_dispatch
{
    OutputIterator operator()(InputIterator begin,InputIterator end,OutputIterator dest)
    {
        return _copy_aux(begin,end,dest,iterator_category(begin));
    }
};
template<typename T>
struct _copy_dispatch<const T*,T*>
{

    T* operator()(const T* begin, const T* end,T*dest)
    {
        typedef typename _type_traits<T>::has_trivial_assignment_operator Type;
        return _copy_argumentPtr(begin,end,dest,Type());
    }
};
template<typename T>
struct _copy_dispatch<T*,T*>
{
    T* operator()(const T* begin, const T* end,T*dest)
    {
        typedef typename _type_traits<T>::has_trivial_assignment_operator Type;
        return _copy_argumentPtr(begin,end,dest,Type());
    }
};
template<typename InputIterator,typename OutputIterator>
OutputIterator copy(InputIterator begin,InputIterator end,OutputIterator dest)
{
    return _copy_dispatch<InputIterator,OutputIterator>()(begin,end,dest);
}

inline char* copy( char* begin,char* end, char* dest)
{
    size_t length = end- begin;
    memmove(dest,begin,length);
    return dest + length;
}
inline wchar_t* copy( wchar_t* begin,wchar_t* end, wchar_t* dest)
{
    size_t length = end- begin;
    memmove(dest,begin,length);
    return dest + length;
}

//merge 要求两个区间都是有序的
template<typename InputIterator1,typename InputIterator2,typename OutputIterator,typename BinaryPred>
OutputIterator merge(InputIterator1 begin1,InputIterator1 end1,
                     InputIterator2 begin2,InputIterator2 end2,
                     OutputIterator dest)
{
    while(begin1 != end1 && begin2 != end2)
    {
        if(*begin1 < *begin2)
        {
            *dest = *begin1;
            ++begin1;
        }
        else
        {
            *dest = *begin2;
            ++begin2;
        }
        ++dest;
    }
    return copy(begin1,end1,copy(begin2,end2,dest));
}
template<typename InputIterator1,typename InputIterator2,typename OutputIterator,typename BinaryPred>
OutputIterator merge(InputIterator1 begin1,InputIterator1 end1,
                     InputIterator2 begin2,InputIterator2 end2,
                     OutputIterator dest,BinaryPred pred)
{
    while(begin1 != end1 && begin2 != end2)
    {
        if(pred(*begin1,*begin2))
        {
            *dest = *begin1;
            ++begin1;
        }
        else
        {
            *dest = *begin2;
            ++begin2;
        }
        ++dest;
    }
    return copy(begin1,end1,copy(begin2,end2,dest));
}

/*****************************************************************************************************/
/**************************迭代器辅助******************************************************************/
//distance
template<typename InputIterator>
typename IteratorTraits<InputIterator>::difference_type
_distance_aux(InputIterator begin,InputIterator end,input_iterator_tag)
{
    typedef typename IteratorTraits<InputIterator>::difference_type difference_type;
    difference_type dis = 0;
    while(begin++ != end) ++dis;
    return dis;
}
template<typename RandomAccessIterator>
typename IteratorTraits<RandomAccessIterator>::difference_type
_distance_aux(RandomAccessIterator begin,RandomAccessIterator end,random_access_iterator_tag)
{
    return end - begin;
}
template<typename Iterator>
typename IteratorTraits<Iterator>::difference_type
distance(Iterator begin,Iterator end)
{
    typedef typename IteratorTraits<Iterator>::iterator_category iterator_category;
    return _distance_aux(begin,end,iterator_category());

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
ForwardItertor search_n(ForwardItertor begin, ForwardItertor end,
                        size_t nobjs,const T& val,BinaryPred pred)
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
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type Distance;
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
    typedef typename IteratorTraits<ForwardIterator>::difference_type Distance;
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
    return lower_bound_aux(begin,end,val,iterator_category());
}
//upper_bound 返回指向第一个大于给定值的迭代器，不存在则返回end
template<typename RandomAccessIterator,typename T>
RandomAccessIterator upper_bound_aux(RandomAccessIterator begin,RandomAccessIterator end,
                                    const T& val,random_access_iterator_tag)
{
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type Distance;
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
    typedef typename IteratorTraits<ForwardIterator>::difference_type Distance;
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
    return upper_bound_aux(begin,end,val,iterator_category());
}

//binary_search
template<typename ForwardIterator,typename T>
bool binary_search(ForwardIterator begin,ForwardIterator end,const T& val)
{
    ForwardIterator iter = lower_bound(begin,end,val);
    return (iter != end) && !(val < *iter);
}
/********************************************************************************/
/******heap相关算法,heap通常以vector作为底层实现,算法要求RandomAccessIterator*******/
/************************************************************************* ******/
//push_heap:要求底层容器的最后一个元素是新插入的元素，
//对最后一个元素进行“上滤（percolate up）”操作以完成Push
template<typename RandomAccessIterator,typename Distance,typename ElementType,typename BinaryFunc>
inline void _percolate_up(RandomAccessIterator begin,Distance slot_index,
                           Distance top_index,ElementType value,BinaryFunc pred)
{
    Distance parent_index = (slot_index - 1)/2;
    while(slot_index > top_index && pred(*(begin + parent_index),value))
    {
        *(begin + slot_index) = *(begin + parent_index);
        slot_index = parent_index;
        parent_index = (slot_index -1)/2;
    }
    *(begin + slot_index )= value;
}
template<typename RandomAccessIterator,typename BinaryPred>
inline void push_heap(RandomAccessIterator begin,RandomAccessIterator end,BinaryPred predicate)
{
    typedef typename IteratorTraits<RandomAccessIterator>::value_type       ElementType;
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type  Distance;
    _percolate_up(begin,Distance(end - begin -1),Distance(0),ElementType(*(end -1)),predicate);

}
template<typename RandomAccessIterator>
inline void push_heap(RandomAccessIterator begin,RandomAccessIterator end)
{
    typedef typename IteratorTraits<RandomAccessIterator>::value_type       Type;
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type  Distance;
    _percolate_up(begin,Distance(end - begin -1),Distance(0),Type(*(end -1)),
                  [](const Type& a, const Type& b){ return a < b;});

}
//pop_heap : 对最大元素执行下滤操作,使其位于底层容器尾部,未真正删除
template<typename RandomAccessIterator,typename Distance,typename ElementType,typename BinaryPred>
inline void _percolate_down(RandomAccessIterator begin,Distance last_element_index,
                          Distance aim_index,ElementType aim_value,BinaryPred predicate)
{
    Distance current_index = aim_index;
    while(current_index < last_element_index)
    {
        Distance left_son = 2 * current_index + 1;
        Distance right_son = left_son + 1;
        Distance bigger_son = current_index;
        if(left_son < last_element_index) // if(leftson < last) there must be a right_son
        {
            bigger_son = predicate( *(begin + right_son),*(begin + left_son) )? left_son : right_son;
        }
        else if(left_son == last_element_index)// left_son is the last, no right_son
        {
            bigger_son = last_element_index;
        }
        else
        {
            break;      //current node does not have son node
        }
        if(predicate(*(begin+current_index) , *(begin+bigger_son)))
        {
            *(begin + current_index) = *(begin + bigger_son);
            *(begin + bigger_son) = aim_value;
        }
        current_index = bigger_son;
    }
}
template<typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator begin,RandomAccessIterator end)
{
    typedef typename IteratorTraits<RandomAccessIterator>::value_type       ElementType;
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type  Distance;
    TinySTL::iter_swap(begin,end-1);
    _percolate_down(begin,Distance(end - begin -2),Distance(0),ElementType(*begin),
                    [](const ElementType& a,const ElementType& b){return a < b;});

}
template<typename RandomAccessIterator,typename BinaryPred>
inline void pop_heap(RandomAccessIterator begin, RandomAccessIterator end,BinaryPred pred)
{
    typedef typename IteratorTraits<RandomAccessIterator>::value_type       ElementType;
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type  Distance;
    TinySTL::iter_swap(begin,end-1);
    _percolate_down(begin,Distance(end - begin -2),Distance(0),ElementType(*begin),pred);
}

//sort_heap:由于pop_heap每次将最大元素置于底层容器尾端而未真正删除，所以只要连续调用pop_heap便可将底层容器排序，
//排序后将不再满足堆序性质。
template<typename RandomAccessIterator>
void sort_heap(RandomAccessIterator begin,RandomAccessIterator end)
{
    while(end != begin)
    {
        pop_heap(begin,end);
        --end;
    }
}
template<typename RandomAccessIterator,typename BinaryPred>
void sort_heap(RandomAccessIterator begin,RandomAccessIterator end,BinaryPred predicate)
{
    while(end != begin)
    {
        pop_heap(begin,end,predicate);
        --end;
    }
}
//make_heap
template<typename RandomAccessIterator>
void make_heap(RandomAccessIterator begin,RandomAccessIterator end)
{
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type  Distance;
    typedef typename IteratorTraits<RandomAccessIterator>::value_type       value_type;
    Distance length = end - begin;
    if(length < 2) return;
    Distance need_percolate_down = (length -2)/2;
    do
    {
        _percolate_down(begin,length-1,need_percolate_down,*(begin+need_percolate_down),
                        [](const value_type& a, const value_type b){ return a < b;});
        --need_percolate_down;
    }while(need_percolate_down >= 0);
}
template<typename RandomAccessIterator,typename BinaryPred>
void make_heap(RandomAccessIterator begin,RandomAccessIterator end,BinaryPred predicate)
{
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type  Distance;
    typedef typename IteratorTraits<RandomAccessIterator>::value_type       value_type;
    Distance length = end - begin;
    if(length < 2) return;
    Distance need_percolate_down = (length -2)/2;
    do
    {
        _percolate_down(begin,length-1,need_percolate_down,*(begin+need_percolate_down),
                        predicate);
        --need_percolate_down;
    }while(need_percolate_down >= 0);
}
//is_heap
template<typename RandomAccessIterator,typename BinaryPred>
bool is_heap(RandomAccessIterator begin,RandomAccessIterator end,BinaryPred predicate)
{
    typedef typename IteratorTraits<RandomAccessIterator>::difference_type  Distance;
    Distance index = 0;
    RandomAccessIterator cur = begin;
    RandomAccessIterator left_son = begin + (2 *index +1);
    const Distance last_element_index = end - begin-1;
    while (left_son <last_element_index)
    {
        if(predicate(*cur,*left_son) || predicate(*cur,*(left_son+1)))
            return false;
        ++cur;
        ++index;
        left_son = begin + (2 *index +1);
    }
    if(left_son == last_element_index && predicate(*cur,*left_son))
        return false;
    return true;
}
template<typename RandomAccessIterator>
bool is_heap(RandomAccessIterator begin,RandomAccessIterator end)
{
    typedef typename IteratorTraits<RandomAccessIterator>::value_type _T;
    is_heap(begin,end,[](const _T& a, const _T& b){ return a < b;});
}

/***********************************************************************************************/
/*                                   划分与排序算法                                             */
/***********************************************************************************************/
//is_partitioned :所有满足pred的元素在不满足pred的元素之前，返回true，否则返回flase，空序列返回true O(N)
template<typename BidirectionalIterator,typename UnaryPred>
bool is_partitioned(BidirectionalIterator begin,BidirectionalIterator end,UnaryPred pred)
{
    while(begin != end)
    {
        if(pred(*begin))
        {
            ++begin;
        }
        else break; //到达第一个不满足要求的元素
    }
    while(begin != end)
    {
        if(pred(*begin))//后面再次出现满足要求的元素，则说明未划分好，返回false
        {
            return false;
        }
        ++begin;
    }
    return true;
}
//partition_copy:所有满足pred的元素copy到dest1,不满足pred的元素copy到dest2,O(N)
template<typename BidirectionalIterator, typename OutputIterator1, typename OutputIterator2,typename UnaryPred>
Pair<OutputIterator1,OutputIterator2> partition_copy(BidirectionalIterator begin, BidirectionalIterator end,
                                                     OutputIterator1 dest1,OutputIterator2 dest2,
                                                     UnaryPred pred)
{
    while (begin != end)
    {
        if(pred(*begin))
        {
            *dest1++ = *begin++;
        }
        else
        {
            *dest2++ = *begin++;
        }
    }
    return make_pair(dest1,dest2);
}
//partition_point:返回第一个不满足pred的元素或end。
//要求输入的序列已划分，即 is_partitioned(begin,end,pred)返回true
template<typename BidirectionalIterator,typename UnaryPred>
BidirectionalIterator partition_point(BidirectionalIterator begin,BidirectionalIterator end,UnaryPred pred)
{
    while(begin != end)
    {
        if(!pred(*begin)) return begin;
        ++begin;
    }
    return begin;
}
//partition:
template<typename BidirectionalIterator,typename UnaryPred>
BidirectionalIterator partition(BidirectionalIterator begin,BidirectionalIterator end,UnaryPred pred)
{
    while (true)
    {
        while (true)
        {
            if(begin == end)
                return begin;
            if(pred(*begin))
                ++begin;
            else
                break;
        }
        --end;
        while(true)
        {
            if(begin == end)
                return begin;
            if(!pred(*end))
                --end;
            else
                break;
        }
        iter_swap(begin,end);
        ++begin;
    }
}
//stable_partion:需利用额外缓冲区
//is_sorted
template<typename RandomAccessIterator>
bool is_sorted(RandomAccessIterator begin,RandomAccessIterator end)
{
    if(begin == end) return true;
    RandomAccessIterator curr = begin;
    ++curr;
    while(curr != end)
    {
        if(*curr < *begin)
            return false;
        ++curr;
    }
    return true;
}
template<typename RandomIterator,typename CompareFunc>
bool is_sorted(RandomIterator begin, RandomIterator end, CompareFunc fun)
{
    if(begin == end) return true;
    RandomIterator curr = begin;
    ++curr;
    while(curr != end)
    {
        if(fun(*curr,*end))
            return false;
        ++curr;
    }
    return true;
}
/**********************************************************************************************/
/*                                    通用重排操作                                             */
/**********************************************************************************************/
//remove_copy
template<typename ForwardIterator,typename OutputIterator,typename T>
OutputIterator remove_copy(ForwardIterator begin,ForwardIterator end,
                           OutputIterator dest,const T& val)
{
    for(;begin != end;++begin)
    {
        if(*begin != val)
        {
            *dest = *begin;
            ++dest;
        }
    }
    return dest;
}
//remove_copy_if
template<typename ForwardIterator,typename OutputIterator,typename UnaryPred>
OutputIterator remove_copy_if(ForwardIterator begin,ForwardIterator end,
                           OutputIterator dest,UnaryPred pred)
{
    for(;begin != end;++begin)
    {
        if(pred(*begin))
        {
            *dest = *begin;
            ++dest;
        }
    }
    return dest;
}
//remove
template<typename ForwardIterator,typename T>
ForwardIterator remove(ForwardIterator begin,ForwardIterator end,const T& val)
{
    ForwardIterator iter = TinySTL::find(begin,end,val);
    ForwardIterator dest = iter;
    if( iter == end) return iter;
    return TinySTL::remove_copy(++iter,end,dest,val);
}
//remove_if
template<typename ForwardIterator,typename UnaryPred>
ForwardIterator remove_if(ForwardIterator begin,ForwardIterator end,UnaryPred pred)
{
    ForwardIterator iter = TinySTL::find_if(begin,end,pred);
    ForwardIterator dest = iter;
    if( iter == end) return iter;
    return TinySTL::remove_copy_if(++iter,end,dest,pred);
}
//unique_copy
template<typename ForwardIterator1,typename ForwardIterator2>
ForwardIterator2 unique_copy(ForwardIterator1 begin,ForwardIterator1 end,ForwardIterator2 dest)
{
    if(begin == end) return dest;
    *dest = *begin;
    ++begin;
    while(begin != end)
    {
        if(*begin != *dest)
        {
            ++dest;
            *dest = *begin;
        }
        ++begin;
    }
    return ++dest;
}

//unique_copy_if
template<typename ForwardIterator1,typename ForwardIterator2,typename BinaryPred>
ForwardIterator2 unique_copy_if(ForwardIterator1 begin,ForwardIterator1 end,
                                ForwardIterator2 dest,BinaryPred pred)
{
    if(begin == end) return dest;
    *dest = *begin;
    ++begin;
    while(begin != end)
    {
        if(pred(*begin,*dest))
        {
            ++dest;
            *dest = *begin;
        }
        ++begin;
    }
    return ++dest;
}
//unique
template<typename ForwardIterator>
ForwardIterator unique(ForwardIterator begin,ForwardIterator end)
{
    if(begin == end) return begin;
    begin = TinySTL::adjacent_find(begin,end);
    return unique_copy(begin,end,begin);
}
template<typename ForwardIterator,typename BinaryPred>
ForwardIterator unique(ForwardIterator begin,ForwardIterator end,BinaryPred pred)
{
    if(begin == end) return begin;
    begin = TinySTL::adjacent_find(begin,end,pred);
    return unique_copy_if(begin,end,begin,pred);
}
//reverse
template<typename BidirectionalIterator>
void _reverse_aux(BidirectionalIterator begin,BidirectionalIterator end,bidirectional_iterator_tag)
{
    while(begin != end)
    {
        if(begin = --end)
            return;
        else
        {
            iter_swap(begin,end);
            ++begin;
        }
    }
}
template<typename RandomAccessIterator>
void _reverse_aux(RandomAccessIterator begin,RandomAccessIterator end,random_access_iterator_tag)
{
    while(begin < end)
    {
        --end;
        iter_swap(begin,end);
        ++begin;
    }
}
//reverse
template <typename BidirectionalIterator>
void reverse(BidirectionalIterator begin, BidirectionalIterator end)
{
    typedef typename IteratorTraits<BidirectionalIterator>::iterator_category category;
    _reverse_aux(begin,end,category());
}

//rotate_copy
template<typename InputIterator,typename OutputIterator>
OutputIterator rotate_copy(InputIterator begin,InputIterator mid,InputIterator end,OutputIterator dest)
{
    return TinySTL::copy(begin,mid,TinySTL::copy(mid,end,dest));
}
//rotate
template<typename BidirectionalIterator>
void _rotate_aux(BidirectionalIterator begin,BidirectionalIterator mid,
                 BidirectionalIterator end,bidirectional_iterator_tag)
{
    TinySTL::reverse(begin,mid);
    TinySTL::reverse(mid,end);
    TinySTL::reverse(begin,end);
}
template<typename ForwardIterator>
void _rotate_aux(ForwardIterator begin,ForwardIterator mid,
                 ForwardIterator end,forward_iterator_tag)
{
    ForwardIterator iter = mid; //由调用该函数的rotate保证初始时begin != mid,mid != end
    while(true)
    {
            iter_swap(begin,iter);
            ++begin;
            ++iter;
        if(begin == mid)//前段结束
        {
            if(iter == end) //后段同时结束
                return;
            mid = iter;
        }
        else if( iter == end)//只有后段结束
        {
            iter = mid;
        }
    }
}
template<typename ForwardIterator>
void rotate(ForwardIterator begin,ForwardIterator mid,ForwardIterator end)
{
    if(begin == mid || mid == end) return;
    typedef typename IteratorTraits<ForwardIterator>::iterator_category category;
    return _rotate_aux(begin,mid,end,category());
}
//next_permutation:将序列置为下一个排列，并返回true。
//已经是最后一个（最大）排列则返回false，并将序列置为第一个（最小）排列
template<typename BidirectionalIterator,typename BinaryPred>
bool next_permutation(BidirectionalIterator begin,BidirectionalIterator end,BinaryPred pred)
{
    if(begin == end) return false; // empty
    BidirectionalIterator iter1 = begin;
    if(++iter1 == end) return false; // only one element
    iter1 = end;
    --iter1;
    for(;iter1 != begin;)
    {
        BidirectionalIterator iter2 = iter1;
        --iter1;
        if(pred(*iter1,*iter2))
        {
            BidirectionalIterator j = end;
            while(!pred(*iter1, *--j));// j point to the first (backward) elementbigger than *iter1
            iter_swap(iter1,j);
            reverse(iter2,end);
            return true;
        }
        if(iter1 == begin)
        {
            reverse(begin,end);
            return false;
        }
    }
}
template<typename BidirectionalIterator>
bool next_permutation(BidirectionalIterator begin,BidirectionalIterator end)
{
    typedef typename IteratorTraits<BidirectionalIterator>::value_type value_type;
    return next_permutation(begin,end,Less<value_type>());

    //use lambda expression
    //return next_permutation(begin,end,[](value_type i1,value_type i2){return i1 < i2;});
}
//pre_permutation:将序列置为上一个排列，并返回true。
//已经是第一个（最小）排列,则返回false，并将序列置为最后一个（最大）排列
template<typename BidirectionalIterator,typename BinaryPred>
bool pre_permutation(BidirectionalIterator begin,BidirectionalIterator end,BinaryPred pred)
{
    if(begin == end) return false; // empty
    BidirectionalIterator iter1 = begin;
    if(++iter1 == end) return false; // only one element
    iter1 = end;
    --iter1;
    for(;iter1 != begin;)
    {
        BidirectionalIterator iter2 = iter1;
        --iter1;
        if(!pred(*iter1,*iter2))
        {
            BidirectionalIterator j = end;
            while(pred(*iter1, *--j));// j point to the first (backward) element less than *iter1
            iter_swap(iter1,j);
            reverse(iter2,end);
            return true;
        }
        if(iter1 == begin)
        {
            reverse(begin,end);
            return false;
        }
    }
}
template<typename BidirectionalIterator>
bool pre_permutation(BidirectionalIterator begin,BidirectionalIterator end)
{
    typedef typename IteratorTraits<BidirectionalIterator>::value_type value_type;
    return pre_permutation(begin,end,Less<value_type>());

    //use lambda expression
    //return pre_permutation(begin,end,[](value_type i1,value_type i2){return i1 < i2;});
}
//is_permutation
template<typename BidirectionalIterator,typename BinaryPred>
bool is_permutation(BidirectionalIterator begin1,BidirectionalIterator end1,
                    BidirectionalIterator begin2,BinaryPred predicate)
{

}
/************************************************************************************************/
/*                                     排序相关算法                                              */
/************************************************************************************************/
//bulbble_sort O(N*N)
template<typename RandomIterator,typename BinaryPred>
void bubble_sort(RandomIterator begin,RandomIterator end,BinaryPred predicate)
{
    bool sorted = true;
    for(; begin != end; --end)
    {
        sorted = true;
        for(auto next = begin + 1; next != end; ++next)
        {
            if(predicate(*next,*(next-1)))
            {
                TinySTL::iter_swap(next,next -1);
                sorted = false;
            }
        }
        if(sorted) return;
    }
}
template<typename RandomIterator>
void bubble_sort(RandomIterator begin,RandomIterator end)
{
    typedef typename IteratorTraits<RandomIterator>::value_type _T;
    bubble_sort(begin,end,[](const _T& a, const _T& b){ return a < b ;});
}
//insertion_sort O(N*N)
template<typename RandomIterator,typename BinaryPred>
void insertion_sort(RandomIterator begin, RandomIterator end,BinaryPred predicate)
{
    if(begin == end) return;
    for(RandomIterator current = begin + 1; current != end; ++current)
    {
        auto current_val = *current;
        RandomIterator iter = current;
        for(; iter != begin;)
        {
            if(predicate(current_val,*(iter-1)))
            {
                *iter = *(iter -1);
                --iter;
            }
            else
            {
                break;
            }
        }
        *iter = current_val;
    }
}
template<typename RandomIterator>
void insertion_sort(RandomIterator begin, RandomIterator end)
{
    typedef decltype(*begin) _T;
    insertion_sort(begin,end,[](const _T& a, const _T&b){ return a < b;});
}
/********************************quick_sort O(N*lgN)***************************************/

//middle_of_3: this is an help function called by quick_sort
template<typename Iterator,typename BinaryPred>
typename IteratorTraits<Iterator>::value_type
middle_of_3(Iterator left,Iterator right,BinaryPred predicate)
{
    Iterator middle = left + (right -left) / 2;
    if(predicate(*middle,*left))
    {
        TinySTL::iter_swap(left,middle);
    }
    if(predicate(*right,*left))
    {
        TinySTL::iter_swap(left,right);
    }
    if(predicate(*right,*middle))
    {
        TinySTL::iter_swap(middle,right);
    }
    TinySTL::iter_swap(middle, right - 1);
    return *(right - 1);
}
template<typename RandomIterator,typename BinaryPred>
void quick_sort(RandomIterator begin,RandomIterator end,BinaryPred predicate)
{
    if(begin == end || begin + 1 == end) return;
    if(end - begin <= 10)
    {
        insertion_sort(begin,end,predicate);
        return;
    }
    typedef typename IteratorTraits<RandomIterator>::value_type value_type;
    value_type mid = middle_of_3(begin,end -1,predicate);
    RandomIterator first = begin;
    RandomIterator last = end - 1;
    for(;;)
    {
        while( predicate(*++first,mid)) ;
        while( predicate(mid,*--last)) ;
        if(first < last)
            TinySTL::iter_swap(first,last);
        else
            break;
    }
    TinySTL::iter_swap(first,end -2);
    quick_sort(begin,first,predicate);
    quick_sort(last, end,predicate);

}
template<typename RandomIterator>
void quick_sort(RandomIterator begin,RandomIterator end)
{
    typedef typename IteratorTraits<RandomIterator>::value_type _T;
    quick_sort(begin,end,[](const _T& a, const _T& b){ return a < b;});
}
//is_sorted
template<typename ForwardIterator,typename BinaryPred>
bool is_sorted(ForwardIterator begin,ForwardIterator end,BinaryPred predicate)
{
    if(begin == end) return true;
    ForwardIterator next = begin;
    ++next;
    while(next != end)
    {
        if(predicate(*next,*begin))
            return false;
        ++next;
    }
    return true;
}
template<typename ForwardIterator>
bool is_sorted(ForwardIterator begin,ForwardIterator end)
{
    typedef typename IteratorTraits<ForwardIterator>::value_type T;
    return is_sorted(begin,end,[](const T& a, const T& b){ return a < b ;});
}
//is_sorted_until
template<typename ForwardIterator,typename BinaryPred>
ForwardIterator is_sorted_until(ForwardIterator begin,ForwardIterator end,BinaryPred predicate)
{
    if(begin == end) return end;
    size_t count = 0;
    size_t max_count = 0;
    ForwardIterator next = begin;
    ++next;
    ForwardIterator result = next;
    while(next != end)
    {
        if(predicate(*next,*begin))
        {
            if(max_count < count)
            {
                result = next;
                max_count = count;
            }
            count = 0;
        }
        else
        {
            count ++;
        }
        ++next;
        ++begin;
    }
    return result;
}
template<typename ForwardIterator>
ForwardIterator is_sorted_until(ForwardIterator begin,ForwardIterator end)
{
    typedef typename IteratorTraits<ForwardIterator>::value_type T;
    return is_sorted_until(begin,end,[](const T& a, const T& b){ return a < b ;});
}
//partial_sort
template<typename RandomIterator,typename BinaryPred>
void partial_sort(RandomIterator begin,RandomIterator middle,
                  RandomIterator end,BinaryPred predicate)
{
    make_heap(begin,middle,predicate);
    RandomIterator iter = middle;
    while(iter != end)
    {
        if(predicate(*begin,*iter))
        {
            TinySTL::iter_swap(begin,iter);
            _percolate_down(begin,middle-begin-1,0,*begin,predicate);
        }
    }
    sort_heap(begin,middle,predicate);
}
template<typename RandomIterator>
void partial_sort(RandomIterator begin,RandomIterator middle,
                  RandomIterator end)
{
    typedef typename IteratorTraits<RandomIterator>::value_type _T;
    partial_sort(begin,middle,end,
                 [](const _T& a,const T& b){ return a < b; });
}
//partial_sort_copy
template<typename ForwardIterator,typename RandomIterator,typename BinaryPred>
RandomIterator partial_sort_copy(ForwardIterator begin,ForwardIterator end,
                                 RandomIterator dest_begin,RandomIterator dest_end,
                                 BinaryPred pred)
{
    size_t input_length = TinySTL::distance(begin,end);
    size_t output_length = TinySTL::distance(dest_begin,dest_end);
    size_t length = min(input_length,output_length);
    ForwardIterator input_iter = begin;
    advance(input_iter,length);
    RandomIterator result =  copy(begin,input_iter,dest_begin);

}

//nth_element
template<typename RandomIterator,typename BinaryPred>
void nth_element(RandomIterator begin, RandomIterator nth,
                 RandomIterator end,BinaryPred predicate)
{
    typedef typename IteratorTraits<RandomIterator>::difference_type    Distance;
    typedef typename IteratorTraits<RandomIterator>::value_type         value_type;
    RandomIterator first = begin;
    RandomIterator last = end;
    value_type value = middle_of_3(first, last,predicate);
}
//
}//namesapce TinySTL
#endif // ALGORITHM_H
