#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H
#include <cstddef>
#include "Alloc.h"
#include "Construct.h"
namespace TinySTL
{
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
private:
    Alloc allocator_;
public:
    T* allocate(size_t nobjs)
    {
        return nobjs == 0 ? nullptr : static_cast<T*>(allocator_.allocate(nobjs * sizeof(T)));
    }
    T* allocate()
    {
        return static_cast<T*>(allocator_.allocate(sizeof(T)));
    }
    void deallocate(T *p, size_t nobjs)
    {
        if( nobjs != 0)
            allocator_.deallocate(static_cast<void*>(p), nobjs*sizeof(T));
    }
    void deallocate(T *p)
    {
        allocator_.deallocate(static_cast<void*>(p),sizeof(T));
    }
    template<typename... Args>
    void construct(T *p,const Args&... args)
    {
        TinySTL::construct(p,TinySTL::forward<T>(args)...);
    }
    void destroy(T* p)
    {
        TinySTL::destroy(p);
    }
    static void destroy(T* first,T* last)
    {
        TinySTL::destroy(first,last);
    }
};
}//命名空间
#endif // ALLOCATOR_H
