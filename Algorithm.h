#ifndef TinySTL_ALGORITHM_H
#define TinySTL_ALGORITHM_H
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

}
#endif // ALGORITHM_H
