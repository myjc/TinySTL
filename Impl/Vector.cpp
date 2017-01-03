#include "../Vector.h"
namespace TinySTL
{
template<typename T,typename Alloc = alloc>
void Vector<T,Alloc>::insert_aux(iterator position, const value_type& val)
{
    if(finish_ != end_of_storage_)
    {
        allocator_.construct(finish_,*(finish_ - 1));
        ++finish_;
        value_type val_copy = val;
        copy_backward(position,finish_-2,finish_ - 1);
        *position = val_copy;
    }
    else
    {
        size_type old_len = size();
        size_type new_len = 0;
        if(old_len == 0)
            new_len = 1;
        else
            new_len = max(2, old_len * 1.5);
        iterator new_start = allocator_.allocate(new_len);
        iterator new_finish = new_start;
        new_finish = uninitialized_copy(start_,position,new_start);
        allocator_.construct(new_finish,val);
        ++new_finish;
        new_finish = uninitialized_copy(position,finish_,new_finish);
        //释放原来位置的元素和空间
        destroy(begin(),end());
        deallocate();
        //调整使指向新空间
        start_ = new_start;
        finish_ = new_finish;
        end_of_storage_ = start_ + new_len;

    }
}
}
