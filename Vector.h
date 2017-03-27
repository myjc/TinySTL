#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H
#include<cstddef>
#include"Allocator.h"
#include"Iterator.h"
#include"Memory.h"
#include"Algorithm.h"
namespace TinySTL
{
template<typename T,typename Alloc = alloc>
class Vector
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef ReverseIterator<iterator> reverse_iterator;
    typedef const ReverseIterator<iterator> const_reverse_iterator;
protected:
    typedef allocator<value_type,Alloc> data_allocator;
private:
    data_allocator allocator_;
    iterator start_;
    iterator finish_;
    iterator end_of_storage_;

public:
    //构造 析构 赋值
    Vector():start_(nullptr),finish_(nullptr),end_of_storage_(nullptr){}
    explicit Vector(size_type nobjs) { fill_initialize(nobjs,value_type());}
    Vector(const size_type& nobjs,const value_type& value) { fill_initialize(nobjs,value);}
    Vector(const Vector& vec):allocator_(vec.allocator_),
        start_(allocator_.allocate(vec.size()))
    {
        finish_ = uninitialized_copy(vec.begin(),vec.end(),start_);
        end_of_storage_ = finish_;
    }

    Vector(Vector&& vec):start_(vec.start_),finish_(vec.finish_),
                         end_of_storage_(vec.end_of_storage_)
    {
        vec.start_ = nullptr;
        vec.finish_ = nullptr;
        vec.end_of_storage_ = nullptr;
    }

    template<typename InputIterator>
    Vector(InputIterator first,InputIterator last)
    {
        size_type len = distance(first,last);
        start_ = allocator_.allocate(len);
        finish_ = uninitialized_copy(first,last,start_);
        end_of_storage_ = finish_;
    }

    Vector& operator=(const Vector& vec);
    Vector& operator=(Vector&& vec)
    {
        start_ = vec.start_;
        finish_ = vec.finish_;
        end_of_storage_ = vec.end_of_storage_;
        vec.start_ = nullptr;
        vec.finish_ = nullptr;
        vec.end_of_storage_ = nullptr;
    }

    ~Vector()
    {
        erase(start_,finish_);
        deallocate();
    }

    //iterator
    iterator begin(){return start_;}
    iterator end() {return finish_;}
    const_iterator cbegin(){ return start_;}
    const_iterator cend(){ return finish_;}
    reverse_iterator rbegin(){ return reverse_iterator(finish_);}
    reverse_iterator rend(){ return reverse_iterator(start_);}
    //容量相关
    size_type size()const{return finish_ - start_;}
    bool empty()const{return finish_ == start_;}
    size_type capacity()const{return end_of_storage_ - start_;}
    void resize(size_type size, value_type val = value_type());

    void reserve(const size_type size)
    {
        if(capacity() < size)
        {
            iterator new_start = allocator_.allocate(size);
            iterator new_finish = uninitialized_copy(begin(),end(),new_start);
            destroy(begin(),end());
            deallocate();
            start_ = new_start;
            finish_ = new_finish;
            end_of_storage_ = finish_;
        }
    }

    void shrink_to_fit()
    {
        if(capacity() > size())
        {
            allocator_.deallocate(finish_,end_of_storage_);
            end_of_storage_ = finish_;
        }
    }

    //元素访问
    reference operator[](const size_type index){return *(start_+index);}
    reference front(){return *begin();}
    reference back(){return *(end()-1);}
    pointer data(){return start_;}
    //容器操作
    void push_back(const value_type& value)
    {
        if(finish_ != end_of_storage_)
        {
            allocator_.construct(finish_,value);
        }
        else
            insert_aux(finish_,value);
    }

    void pop_back()
    {
        --finish_;
        allocator_.destroy(finish_);
    }
    void clear()
    {
        erase(begin(),end());
    }

    iterator erase(iterator position)
    {
        if(position + 1 != end())
            copy(position + 1,finish_,position);
        --finish_;
        allocator_.destroy(finish_);
        return position;
    }
    template<typename Iterator>
    iterator erase(Iterator first,Iterator last)
    {
        iterator iter = copy(last,finish_,first);
        allocator_.destroy(iter,finish_);
        finish_ = finish_ - (last - first);
        return first;
    }

    iterator insert(iterator position,const value_type& value)
    {
         return insert_aux(position,value);
    }

    template<typename InputIterator>
    iterator insert(iterator position,InputIterator first, InputIterator last);
    iterator insert(iterator position, size_type nobjs,const value_type &value);
    void swap(Vector& vec);
private:
    //help methods
    iterator allocate_and_fill(size_t nobjs,const value_type& val)
    {
        iterator result = allocator_.allocate(nobjs);
        uninitialized_fill_n(result,nobjs,val);
        return result;
    }
    void fill_initialize(size_type n, const value_type& val)
    {
        start_ = allocate_and_fill(n,val);
        finish_ = start_ + n;
        end_of_storage_ = finish_;
    }
    void deallocate()
    {
        allocator_.deallocate(start_,end_of_storage_ - start_);
    }

    iterator insert_aux(iterator position,const value_type& val);
};//Vector
}//namesapce TinySTL
#endif // VECTOR_H
