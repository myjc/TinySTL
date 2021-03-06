#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H

#include<new>
#include "TypeTraits.h"
#include "Utility.h"

namespace TinySTL {
template<typename T,typename ...Value>
inline void construct(T* ptr,const Value&... value)
{
    new (ptr) T(TinySTL::forward<T>(value)...);
}
template<typename T>
inline void destroy(T* pointer)
{
    pointer->~T();
}

// has trival constructor
template<typename ForwardIterator>
inline void _destroy_depend_type(ForwardIterator first,ForwardIterator last,_true_type){}

//has nontrival constructor
template<typename ForwardIterator>
inline void _destroy_depend_type(ForwardIterator first,ForwardIterator last,_false_type)
{
    for(; first < last; first++)
        destroy(&*first);
}
template<typename ForwardIterator,typename T>
inline void _destroy(ForwardIterator first,ForwardIterator last,T*)
{
    typedef typename _type_traits<T>::has_trivial_destructor trivial_destructor;
    _destroy_depend_type(first,last,trivial_destructor());

}
template<typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
    _destroy(first,last, value_type(first));
}

//template specialization for char, wchar_t
inline void destroy(char*, char*){}

inline void destroy(wchar_t*, wchar_t*){}
}

#endif // CONSTRUCT_H
