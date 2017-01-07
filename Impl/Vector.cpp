#include "../Vector.h"
namespace TinySTL
{
template<typename T,typename Alloc>
iterator Vector<T,Alloc>::insert_aux(iterator position, const value_type& val)
{
    if(finish_ != end_of_storage_)
    {
        allocator_.construct(finish_,*(finish_ - 1));
        ++finish_;
        value_type val_copy = val;
        copy_backward(position,finish_-2,finish_ - 1);
        *position = val_copy;
        return position;
    }
    else
    {
        size_type old_len = size();
        size_type new_len = 0;
        if(old_len == 0)
            new_len = 1;
        else
            new_len = max(size_type(2), old_len * 2);
        iterator new_start = allocator_.allocate(new_len);
        iterator new_finish = new_start;
        new_finish = uninitialized_copy(start_,position,new_start);
        iterator result = new_finish; // return value
        allocator_.construct(new_finish,val);
        ++new_finish;
        new_finish = uninitialized_copy(position,finish_,new_finish);
        //释放原来位置的元素和空间
        allocator_.destroy(begin(),end());
        deallocate();
        //调整使指向新空间
        start_ = new_start;
        finish_ = new_finish;
        end_of_storage_ = start_ + new_len;
        return result;
    }
}//insert_aux
template<typename T,typename Alloc>
void Vector<T,Alloc>::resize(size_type new_size, value_type val)
{
    if(new_size < size())
    {
        iterator iter = start_ + new_size;
        erase(iter,finish_);
    }
    else if(new_size < capacity())
    {
        iterator iter = start_ + new_size;
        uninitialized_fill(finish_,iter,val);
        finish_ = iter;
    }
    else if(new_size > capacity())
    {
        size_type old_size = size();
        iterator new_start = allocator_.allocate(new_size);
        iterator new_finish_ = uninitialized_copy(start_,finish_,new_start);
        new_finish_ = uninitialized_fill_n(finish_,new_size - old_size,val);
        allocator_.destroy(begin(),end());
        deallocate();
        start_ = new_start;
        finish_ = new_finish_;
        end_of_storage_ = finish_;
    }
}//resize
template<typename T,typename Alloc>
iterator Vector<T,Alloc>::insert(iterator position,size_type nobjs,const value_type& value)
{
    if(capacity() - size() >= nobjs)
    {
        size_type elements_after = finish_ - position;//插入点之后的元素个数
        if(elements_after >= nobjs)
        {
            uninitialized_copy(finish_ - nobjs,finish_,finish_);
            copy_backward(position,finish_ - nobjs,finish_);
            fill_n(position,nobjs,value);
            finish_ += nobjs;
            return position;
        }
        else
        {
            iterator new_finish = uninitialized_fill_n(finish_, nobjs - elements_after,value);
            finish_ = uninitialized_copy(position,finish_,new_finish);
            fill_n(position,elements_after,value);
            return position;
        }
    }
    else
    {
        iterator new_start = allocator_.allocate(size() + nobjs);
        iterator new_finish = uninitialized_copy(begin(),position,new_start);
        iterator result = new_finish; // return result
        new_finish = uninitialized_fill_n(new_finish,nobjs,value);
        new_finish = uninitialized_copy(position,finish_,new_finish);
        allocator_.destroy(begin(),end());
        deallocate();
        start_ = new_start;
        finish_ = new_finish;
        end_of_storage_ = new_finish;
        return result;
    }
}
}
