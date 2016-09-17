#include "../Alloc.h"

namespace TinySTL
{
    //memory heap initialize
    char *alloc::start_free = nullptr;
    char *alloc::end_free = nullptr;
    size_t alloc::heap_size = 0;
    alloc::obj* alloc::free_list[_NFREELISTS] = {0};

    void* alloc::allocate(size_t bytes)
    {
        if(bytes > _MAX_BYTES)
            return malloc(bytes);
        obj **my_free_list;
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
        obj **my_free_list = free_list + FREELIST_INDEX(n);
        node ->next_free_chunk = *my_free_list;
        *my_free_list = node;
    }
    void* alloc::refill(size_t bytes)
    {
        int nobjs = _NOBJECTS;
        char *chunk = chunk_alloc(bytes,nobjs);
        if(nobjs == 1)
            return chunk;
        obj **my_free_list = free_list + FREELIST_INDEX(bytes);
        obj *result = static_cast<obj*>(chunk);
        obj *next_obj = static_cast<obj*>(chunk +n);
        obj *current_obj = nullptr;
        *my_free_list = next_obj;
        for(int i = 0;;i++) //return the first one,remains nobjs-1;
        {
            current_obj = next_obj;
            next_obj = static_cast<obj*>(static_cast<char*>(next_obj)+bytes);
            if(nobjs -1 == i)
            {
                current_obj->next_free_chunk = nullptr;
                break;
            }
            else
            {
                current_obj->next_free_chunk = next_obj;
            }

        }
        return result;

    }
    char* alloc::chunk_alloc(size_t size, int &nobjs)
    {
        char *result= nullptr;
        size_t total_bytes = size * nobjs;
        size_t bytes_left = end_free - start_free;
        //memory pool is big enough
        if(bytes_left >= total_bytes)
        {
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        //memory pool can afford more than one obj
        else if(bytes_left >= size)
        {
            nobjs = bytes_left / size;
            total_bytes = size * nobjs;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        //smaller than one obj
        else
        {
           size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);

           if(bytes_left > 0)
           {
               obj **my_free_list = free_list+FREELIST_INDEX(bytes_left);
               obj *left_chunk = static_cast<obj*>(start_free);
               left_chunk->next_free_chunk = *my_free_list;
               *my_free_list = left_chunk;
           }
           start_free = static_cast<char*>(malloc(bytes_to_get));
           if(start_free == nullptr)
           {
               obj **my_free_list = nullptr,*node = nullptr;
               for(size_t i = size; i <= _MAX_BYTES; i += _ALIGN)
               {
                   my_free_list = free_list + FREELIST_INDEX(i);
                   node = *my_free_list;
                   if(node != nullptr)
                   {
                       (*my_free_list)->next_free_chunk = node->next_free_chunk;
                       start_free = static_cast<char*>(node);
                       end_free = start_free + i;
                       return chunk_alloc(size,nobjs);
                   }

               }
           end_free == nullptr;

           }
           heap_size += bytes_to_get;
           end_free = start_free + bytes_to_get;
           return chunk_alloc(size,nobjs);
        }


    }
}//namespace TinySTL
