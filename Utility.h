#ifndef TinySTL_UTILITY_H
#define TinySTL_UTILITY_H
#include "TypeTraits.h"
namespace TinySTL
{
//swap
template<typename T> void swap(T& v1, T& v2)
{
    T temp = v1;
    v1 = v2;
    v2 = temp;
}
//pair
template<typename First,typename Second>
class Pair
{
public:
    First first;
    Second second;
public:
    Pair() = default;
    Pair(const Pair&) = default;
    Pair(const First& f, const Second& s):first(f),second(s){}
    Pair& operator=(const Pair& p)
    {
        first = p.first;
        second = p.second;
        return *this;
    }
    ~Pair() = default;
    void swap(Pair& p1, Pair& p2)
    {
        TinySTL::swap(p1.first,p2.first);
        TinySTL::swap(p1.second,p2.second);
    }

};
template<typename First,typename Second>
bool operator== (const Pair<First,Second>& p1, const Pair<First,Second>& p2)
{
    return p1.first == p2.first && p1.second == p2.second;
}
template<typename First,typename Second>
bool operator!= (const Pair<First,Second>& p1, const Pair<First,Second>& p2)
{
    return !(p1 == p2);
}
template<typename First,typename Second>
bool operator< (const Pair<First,Second>& p1, const Pair<First,Second>& p2)
{
    return (p1.first < p2.first) || (!(p2.first < p1.first) && (p1.second < p2.second));
}
template<typename First,typename Second>
bool operator<= (const Pair<First,Second>& p1, const Pair<First,Second>& p2)
{
    return p1 < p2 || p1 == p2;
}
template<typename First,typename Second>
bool operator>= (const Pair<First,Second>& p1, const Pair<First,Second>& p2)
{
    return p2 < p1 || p2 == p1;
}
template<typename First,typename Second>
bool operator> (const Pair<First,Second>& p1, const Pair<First,Second>& p2)
{
    return p2 < p1;
}
template<typename First,typename Second>
inline Pair<First,Second> make_pair(const First& f, const Second& s)
{
    return Pair<First,Second>(f,s);
}
// move
template<typename T>
typename RemoveReference<T>::type&& move(T&& val)
{
    return static_cast<typename RemoveReference<T>::type&&>(val);
}
template<typename T>
T&& forward(typename RemoveReference<T>::type& val)
{
    return static_cast<T&&>(val);
}
template<typename T> T&& forward(typename RemoveReference<T>::type&& val)
{
    return static_cast<T&&>(val);
}
}
#endif // UTILITY_H
