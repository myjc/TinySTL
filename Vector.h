#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H
#include<cstddef>
#include"Allocator.h"
#include"Iterator.h"
#include"Memory.h"
namespace TinySTL
{
template<typename T,typename Alloc = alloc> class Vector
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
protected:
    typedef allocator<value_type,Alloc> data_allocator;
private:
    iterator start_;
    iterator finish_;
    iterator end_of_storage_;
public:
    //构造 析构 赋值
    Vector():start_(nullptr),finish_(nullptr),end_of_storage_(nullptr){}
    explicit Vector(const size_type& objs);
    Vector(const size_type& objs,const value_type& value);
    Vector(const Vector& vec);
    Vector(Vector&& vec);
    template<typename InputIterator>
    Vector(InputIterator first,InputIterator last);

    Vector& operator=(const Vector& vec);
    Vector& operator=(Vector&& vec);

    ~Vector();
    //iterator
    iterator begin(){return start_;}
    iterator end() {return finish_;}
    reverse_iterator rbegin(){ return reverse_iterator(finish_);}
    reverse_iterator rend(){ return reverse_iterator(start_);}
    //容量相关
    size_type size()const{return finish_ - start_;}
    bool empty()const{return finish_ == start_;}
    size_type capacity()const{return end_of_storage_ - start_;}
    void resize(const size_type size, value_type val = value_type());
    void reserve(const size_type size);
    void shrink_to_fit();
    //元素访问
    reference operator[](const size_type index){return *(start_+index);}
    reference at(const size_type index);
    reference front(){return *begin();}
    reference back(){return *(end()-1);}
    pointer data(){return start_;}
    //容器操作
    void push_back(const value_type& value);
    void pop_back();
    void clear();
    iterator erase(iterator position);
    template<typename InputIterator>
    void erase(InputIterator first,InputIterator last);
    iterator insert(iterator position,const value_type& value);
    template<typename InputIterator>
    void insert(iterator position,InputIterator first, InputIterator last);
    void insert(iterator position, const size_type nobjs,const value_type &value);
private:
    //help methods
    void realloc_and_copy(size_t nobjs)
    {
        iterator new_start;
    }





};//Vector
}//namesapce TinySTL
#endif // VECTOR_H
