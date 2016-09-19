#ifndef UNINITIALIZE_H
#define UNINITIALIZE_H
#include "TypeTraits.h"
#include "Iterator.h"
#include "Construct.h"
namespace TinySTL
{

/*********************************************************************/
template<typename ForwardIterator,typename Size,typename T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator iter,Size n,const T& x)
{
    return _uninitialized_fill_n(iter,n,x,value_type(iter));
}
template<typename ForwardIterator,typename Size,typename T,typename T1>
inline ForwardIterator _uninitialized_fill_n(ForwardIterator iter,Size n,const T& x,T*)
{
    typedef typename _type_traits<T1>::is_POD_type is_POD;
    return _uninitialized_fill_n_aux(iter,n,x,is_POD());
}

/*
template<typename ForwardIterator,typename Size,typename T>
inline ForwardIterator _uninitialized_fill_n_aux(ForwardIterator iter,Size n,const T& x,_true_type)
{
    //todo :call fill_n()
}
*/
template<typename ForwardIterator,typename Size,typename T>
inline ForwardIterator _uninitialized_fill_n_aux(ForwardIterator iter,Size n,const T& x,_false_type)
{
    ForwardIterator curr = iter;
    for(; n >0; --n)
    {
        construct(&*curr,x);
        ++curr;
    }
    return curr;
}

/*********************************************************************/
template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first,InputIterator last, ForwardIterator dest)
{
    return _uninitialized_copy(first,last,dest,value_type(dest));

}
template<typename InputIterator, typename ForwardIterator,typename T>
inline ForwardIterator _uninitialized_copy(InputIterator first,InputIterator last, ForwardIterator dest,T*)
{
    typedef typename _type_traits<T>::is_POD_type is_POD;
    return _uninitialized_copy_aux(first,last,dest,is_POD());

}



/*
template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator _uninitialized_copy_aux(InputIterator first,InputIterator last,
                                               ForwardIterator dest,_true_type)
{
//todo : call copy();
}
*/
template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator _uninitialized_copy_aux(InputIterator first,InputIterator last,
                                               ForwardIterator dest,_false_type)
{
    ForwardIterator iter = dest;
    for(; first != last; first++,iter++)
    {
        construct(&*iter, *first);
    }
    return iter;

}

/*********************************************************************/
template<typename ForwardIterator,typename T>
inline void uninitialized_fill(ForwardIterator first,ForwardIterator last, const T &x)
{
    _uninitialized_fill(first,last,x,value_type(first));
}
template<typename ForwardIterator,typename T,typename T1>
inline void _uninitialized_fill(ForwardIterator first,ForwardIterator last, const T &x,T1*)
{
    typedef typename _type_traits<T1>::is_POD_type is_POD;
    _uninitialized_fill_aux(first,last,x,is_POD());
}
template<typename ForwardIterator,typename T>
inline void _uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,
                                               const T &x,_false_type)
{
    for(; first != last; first++)
    {
        construct(&*first,x);
    }
}
/*
template<typename ForwardIterator,typename T>
inline void _uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,
                                               const T &x,_true_type)
{
    todo : call fill()
}
*/
}//namespace TinySTL

#endif // UNINITIALIZE_H
