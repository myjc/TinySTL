#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <cstddef>
namespace TinySTL
{

class alloc; // allocate deallocate Impl

template<typename T>
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
    static T* allocate(size_t n)
    {
        return n == 0 ? nullptr : static_cast<T*>(alloc::allocate(n * sizeof(T)));
    }
    static T* allocate()
    {
        return static_cast<T*>(alloc::allocate(sizeof(T)));
    }
    static void deallocate(T *p, size_t n)
    {
        if( n != 0)
            alloc::deallocate(p, n*sizeof(T));
    }
    static void deallocate(T *p)
    {
        alloc::deallocate(p,sizeof(T));
    }

};
}
#endif // ALLOCATOR_H
