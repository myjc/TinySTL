#ifndef TinySTL_ALLOC_H
#define TinySTL_ALLOC_H
#include <cstddef>
#include <cstdlib>
namespace TinySTL
{

enum { _ALIGN = 8};
enum { _MAX_BYTES = 128};
enum { _NFREELISTS = _MAX_BYTES / _ALIGN };
enum { _NOBJECTS = 20};

class alloc
{
private:
    static size_t ROUND_UP(size_t bytes)
    {
        return ((bytes+_ALIGN -1) & ~(_ALIGN - 1));
    }
    static size_t FREELIST_INDEX(size_t bytes)
    {
        return ((bytes + _ALIGN - 1)/ _ALIGN -1);
    }
private:
    union obj
    {
        union obj *next_free_chunk;
        char client_data[1];
    };
private:
    static obj *free_list[_NFREELISTS];

    static void *refill(size_t n);
    static char * chunk_alloc(size_t size, int &nobjs);

    // memery pool
    static char *start_free;
    static char *end_free;
    static size_t heap_size;
public:
    static void *allocate(size_t n);
    static void deallocate(void *ptr,size_t n);
    static void *reallocate(void *ptr, size_t odd_size,size_t new_size);
};
}//namespace TinySTL
#endif // ALLOC_H
