#ifndef TINYSTL_ALGORITHM_H
#define TINYSTL_ALGORITHM_H
#include <cstring>
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
inline void fill(wchar_t* first, wchar_t last, const wchar_t& value)
{
     memset(first, static_cast<unsigned char>(value),(last - first)*sizeof(wchar_t));
}
//fill_n(beg,n,val)
template<typename ForwardIterator,typename T>
void fill_n(ForwardIterator pos,const size_t n,const T& value)
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

//**************************************************************//
//*************************查找对象的算法************************//

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
inline size_t count(InputIterator beg,InputIterator end,const T& val)
{
    size_t quantity = 0;
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
inline size_t count_if(InputIterator beg,InputIterator end,Func func)
{
    size_t quantity = 0;
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

}//namesapce TinySTL
#endif // ALGORITHM_H
