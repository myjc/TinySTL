#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H
#include <cstddef>
#include "Alloc.h"
#include "Construct.h"
namespace TinySTL
{

class alloc; // allocate deallocate Impl

template<typename T,typename Alloc = alloc>
class allocator
{
public:
    typedef T   value_type;
    typedef T*  pointer;
    typedef T&  reference;
    typedef const T*    const_pointer;
    typedef const T&    const_reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
public:
    static T* allocate(size_t nobjs)
    {
        return nobjs == 0 ? nullptr : static_cast<T*>(Alloc::allocate(nobjs * sizeof(T)));
    }
    static T* allocate()
    {
        return static_cast<T*>(Alloc::allocate(sizeof(T)));
    }
    static void deallocate(T *p, size_t nobjs)
    {
        if( nobjs != 0)
            Alloc::deallocate(p, nobjs*sizeof(T));
    }
    static void deallocate(T *p)
    {
        Alloc::deallocate(p,sizeof(T));
    }
    template<typename Args>
    static void construct(T *p,const Args& args)
    {
        TinySTL::construct(p,args);
    }
    static void destroy(T* p)
    {
        TinySTL::destroy(p);
    }

};
}//命名空间
#endif // ALLOCATOR_H
