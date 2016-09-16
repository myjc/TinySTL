#include "../Alloc.h"

namespace TinySTL
{
    //memory heap initialize
    char *alloc::start_free = nullptr;
    char *alloc::end_free = nullptr;
    size_t alloc::heap_size = 0;

    void *alloc::allocate(size_t bytes)
    {
        if(bytes > _MAX_BYTES)
            return malloc(bytes);
        obj *my_free_list;
        obj *result;
        my_free_list = free_list + FREELIST_INDEX(bytes);
        result = *my_free_list;
        if(result == nullptr)
        {
            void *r = refill(ROUND_UP(bytes));
            return r;
        }
        *my_free_list = result->next_free_chunk;
        return result;

    }
    void alloc::deallocate(void *ptr, size_t n)
    {
        if(n > _MAX_BYTES)
            free(ptr);
        obj *node = static_cast<obj*>(ptr);
        obj *my_free_list = free_list + FREELIST_INDEX(n);
        node ->next_free_chunk = *my_free_list;
        *my_free_list = node;
    }
}
